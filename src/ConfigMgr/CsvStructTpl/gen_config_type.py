#! /usr/bin/env python



import os
import sys
import glob
import getopt
import csv
import logging
import string
import codecs

from datetime import datetime
from string import Template

whiteList = {"Attribute", "BattleConfig", "Hero", "HeroAttribute", "DestructiveObjects", "DestructiveObjectsEvent", "Troop"}

def usage():  
    print("Usage:%s --inDir --tplDir --outFile " % sys.argv[0]); 

def getConfigStructName(aConfigName):
    return "Config" + aConfigName

def GenerateStruct(aStructTpl, aConfName, aFieldNameList, aFieldTypeList):
    
    if len(aFieldNameList) != len(aFieldTypeList):
        logging.warning("conf:%s fieldName:%s fieldType:%s" % (aConfName, ','.join(aFieldNameList), ','.join(aFieldTypeList)))
        return ""

    typeToCType = {
        "int":      "int64",
        "float":    "float",
        "string":   "string",
		"assetpath":   "string",
        "assetpath[]":   "vector<string>",
        "sceneconf":   "string",
        "sceneconf[]":   "vector<string>",
        "int[]":    "vector<int64>",
        "float[]":  "vector<float>",
        "string[]":"vector<string>",
        "string[][]":"vector<vector<string>>",
        "int[][]":  "vector<vector<int64> >",
        "float[][]":"vector<vector<float> >",
    }
    unserializeCode = {
        "int":      Template("${FIELD_NAME} = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[${INDEX}] ],0);"),
        "float":    Template("${FIELD_NAME} = convertFromStr<float>(aColArr[mapStructFieldToCsvField[${INDEX}] ],0);"),
        "string":   Template("${FIELD_NAME} = aColArr[mapStructFieldToCsvField[${INDEX}] ];"),
		"assetpath":   Template("${FIELD_NAME} = aColArr[mapStructFieldToCsvField[${INDEX}] ];"),
        "assetpath[]":   Template("${FIELD_NAME} = convertToVector<string>(aColArr[mapStructFieldToCsvField[${INDEX}] ],\"\");"),
        "sceneconf":   Template("${FIELD_NAME} = aColArr[mapStructFieldToCsvField[${INDEX}] ];"),
        "sceneconf[]":   Template("${FIELD_NAME} = convertToVector<string>(aColArr[mapStructFieldToCsvField[${INDEX}] ],\"\");"),
        "int[]":    Template("${FIELD_NAME} = convertToVector<int64>(aColArr[mapStructFieldToCsvField[${INDEX}] ],0);"),
        "float[]":  Template("${FIELD_NAME} = convertToVector<float>(aColArr[mapStructFieldToCsvField[${INDEX}] ],0);"),
        "string[]": Template("${FIELD_NAME} = convertToVector<string>(aColArr[mapStructFieldToCsvField[${INDEX}] ],\"\");"),
        "int[][]":  Template("${FIELD_NAME} = convertToVector2<int64>(aColArr[mapStructFieldToCsvField[${INDEX}] ],0);"),
        "string[][]": Template("${FIELD_NAME} = convertToVector2<string>(aColArr[mapStructFieldToCsvField[${INDEX}] ],\"\");"),
        "float[][]":Template("${FIELD_NAME} = convertToVector2<float>(aColArr[mapStructFieldToCsvField[${INDEX}] ],0);"),    
    }
    
    forcsv2lua = """
    /*FOR2LUA
        <Record>
            <name>${CONF_STRUCT_NAME}</name>
            <Function>
                <name>Get${FIELD_NAME}</name>
                <replaceName>${FIELD_NAME}</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    """

    getCode =  {
        "int":      Template(forcsv2lua+"""inline int64 Get${FIELD_NAME}() const
    {
        return m${FIELD_NAME};
    } """),
        "float":    Template(forcsv2lua+"""inline float Get${FIELD_NAME}() const
    {
        return m${FIELD_NAME};
    } """),
        "string":   Template(forcsv2lua+"""inline const string& Get${FIELD_NAME}() const
    {
        return m${FIELD_NAME};
    } """),
		"assetpath":   Template(forcsv2lua+"""inline const string& Get${FIELD_NAME}() const
    {
        return m${FIELD_NAME};
    } """),
        "assetpath[]":  Template(forcsv2lua+"""inline const vector<string>& Get${FIELD_NAME}() const
    {
        return m${FIELD_NAME};
    } """),
        "sceneconf":   Template(forcsv2lua+"""inline const string& Get${FIELD_NAME}() const
    {
        return m${FIELD_NAME};
    } """),
        "sceneconf[]":  Template(forcsv2lua+"""inline const vector<string>& Get${FIELD_NAME}() const
    {
        return m${FIELD_NAME};
    } """),
        "int[]":    Template(forcsv2lua+"""inline const vector<int64>& Get${FIELD_NAME}() const
    {
        return m${FIELD_NAME};
    } """),
        "float[]":  Template(forcsv2lua+"""inline const vector<float>& Get${FIELD_NAME}() const
    {
        return m${FIELD_NAME};
    } """),
        "string[]":  Template(forcsv2lua+"""inline const vector<string>& Get${FIELD_NAME}() const
    {
        return m${FIELD_NAME};
    } """),
        "string[][]":  Template(forcsv2lua+"""inline const vector<vector<string>>& Get${FIELD_NAME}() const
    {
        return m${FIELD_NAME};
    } """),
        "int[][]":  Template(forcsv2lua+"""inline const vector<vector<int64> >& Get${FIELD_NAME}() const
    {
        return m${FIELD_NAME};
    } """),
        "float[][]":Template(forcsv2lua+"""inline const vector<vector<float> >& Get${FIELD_NAME}() const
    {
        return m${FIELD_NAME};
    } """),
    }

    fieldNameList = []
    fieldTypeList = []
    fieldDeclareList = []
    fieldUnserializeList = []
    fieldGetList = []
    i = 0
    num = len(aFieldNameList)
    while i < num:
        fieldName = aFieldNameList[i]
        fieldType = aFieldTypeList[i]

        fieldName = fieldName[0].capitalize() + fieldName[1:]
        if  fieldType not in typeToCType:
            logging.warning("conf:%s fieldName:%s has invalid fieldType:%s" % (aConfName, fieldName, fieldType ))
            return ""
        fieldNameList.append('"'+fieldName+'"')
        fieldTypeList.append('"'+fieldType+'"')
        fieldDeclareList.append( "    %s m%s;" % (typeToCType[fieldType], fieldName) )
        fieldUnserializeList.append( unserializeCode[fieldType].substitute( INDEX=i, FIELD_NAME = "m"+fieldName )  )
        fieldGetList.append( getCode[fieldType].substitute( INDEX=i, FIELD_NAME=fieldName, CONF_STRUCT_NAME=getConfigStructName(aConfName) )  ) 
        i += 1

    lines = aStructTpl.substitute(
                    STRUCT_NAME = getConfigStructName(aConfName),
                    FIELD_NUM = len(fieldDeclareList),
                    FIELD_NAME_LIST = ",".join(fieldNameList),
                    FIELD_TYPE_LIST = ",".join(fieldTypeList),
                    FIELD_UNSERIALIZE = "\n        ".join(fieldUnserializeList),
                    FIELD_GET = "\n    ".join(fieldGetList),
                    FIELD_LIST = "\n".join(fieldDeclareList))

    return ''.join(lines)
  

def GenerateHpp(aInDir, aTplDir, aOutFile):
    csvList = glob.glob(aInDir + '/*.csv' )

    structTplFile = open(aTplDir + '/ConfStruct.template','r')
    structTpl = Template(structTplFile.read())

    hppTplFile = open(aTplDir + '/ConfType_h.template','r')
    hppTpl = Template(hppTplFile.read())

    hppFile = open(aOutFile,'w')
    
    structList = []
    getStructList = []
    for csvFile in csvList:
        confName = os.path.basename(csvFile)
        confName = confName.replace(".csv", "")
        confName = confName[0].capitalize() + confName[1:]

        if confName not in whiteList:
            continue
        # if confName == "SLGBuildingCfg" or confName == "Example" or confName == "MarchOrder":
        #     continue
        print (confName)
        
        logging.debug("start deal config:%s" % confName)

        fp = open(csvFile)
        line = fp.readline()
        if line[:3] == codecs.BOM_UTF8:
            line = line[3:]

        fieldNameList = map( lambda s:s.strip(' '), list(csv.reader([line]))[0])

        line = fp.readline()
        fieldTypeList = map( lambda s:s.strip(' '), list(csv.reader([line]))[0])

        structContent = GenerateStruct(structTpl, confName, fieldNameList, fieldTypeList)
        if structContent == "":
            logging.error("generate struct for %s failed" % confName)
            continue

        structList.append(structContent)

        getStructList.append(Template("""if( strcmp(aTableName, "${CONF_STRUCT_NAME}") == 0 )
        {
            return new ${CONF_STRUCT_NAME}();
        }""").substitute(CONF_STRUCT_NAME=getConfigStructName(confName)))

    #end for

    lines = hppTpl.substitute(
                DATE = datetime.now().strftime('%Y-%m-%d %H:%M:%S'),
                STRUCT_LIST = '\n'.join(structList),
                GET_STRUCT_LIST = '\n        '.join(getStructList))

    hppFile.writelines(lines)
    hppFile.close();
if __name__ == '__main__':  

    optList, args = getopt.getopt(sys.argv[1:], '', ['inDir=', 'tplDir=', 'outFile='])

    inDir = "../../../../../../../Design/conf/conf_dev/confdb/csv"
    if sys.argv[0].find("native_dev"):
        inDir = "../../../../../../../../Design/conf/conf_dev/confdb/csv"
    tplDir = "."
    outFile = "../CsvType_auto.h"
    for opt, val in optList:
        if opt == "--inDir":
            inDir = val
        elif opt == "--tplDir":
            tplDir = val
        elif opt == "--outFile":
            outFile = val
        else:
            print ("invalid param %s = %s" % (opt, val))
            usage()
            sys.exit(1);

    # logging.basicConfig(level=logging.DEBUG,
    #             format='[%(asctime)s][%(filename)s:%(lineno)d][%(levelname)s] %(message)s',
    #             datefmt='%a, %d %b %Y %H:%M:%S')
    logging.basicConfig(level=logging.WARNING,
                filename='gen.log',
                filemode='w',
                format='[%(asctime)s][%(filename)s:%(lineno)d][%(levelname)s] %(message)s',
                datefmt='%a, %d %b %Y %H:%M:%S')
    GenerateHpp(inDir, tplDir, outFile)  
