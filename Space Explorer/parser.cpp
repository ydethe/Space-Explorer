//
//  parser.cpp
//  Space Explorer
//
//  Created by Yann Blaudin de Thé on 22/09/11.
//  Copyright 2011 EADS Astrium ST. All rights reserved.
//

#include "parser.h"

using namespace xercesc;

/**
 *  Constructor initializes xerces-C libraries.
 *  The XML tags and attributes which we seek are defined.
 *  The xerces-C DOM parser infrastructure is initialized.
 */

VesselConfig::VesselConfig()
{
    try
    {
        XMLPlatformUtils::Initialize();  // Initialize Xerces infrastructure
    }
    catch( XMLException& e )
    {
        char* message = XMLString::transcode( e.getMessage() );
        std::cerr << "XML toolkit initialization error: " << message << std::endl;
        XMLString::release( &message );
        // throw exception here to return ERROR_XERCES_INIT
    }
    
    // Tags and attributes used in XML file.
    // Can't call transcode till after Xerces Initialize()
    TAG_root    = XMLString::transcode("root");
    TAG_General = XMLString::transcode("General");
    TAG_Physics = XMLString::transcode("Physics");
    TAG_Engine  = XMLString::transcode("Engine");
    TAG_Tank    = XMLString::transcode("Tank");
    
    // General
    ATTR_name = XMLString::transcode("name");
    
    //Physics
    ATTR_mass = XMLString::transcode("mass");
    ATTR_Ixx = XMLString::transcode("Ixx");
    ATTR_Iyy = XMLString::transcode("Iyy");
    ATTR_Izz = XMLString::transcode("Izz");
    ATTR_Ixy = XMLString::transcode("Ixy");
    ATTR_Ixz = XMLString::transcode("Ixz");
    ATTR_Iyz = XMLString::transcode("Iyz");
    
    // Engine
    ATTR_type = XMLString::transcode("type");
    ATTR_mass_flow = XMLString::transcode("mass_flow");
    
    // Tank
    ATTR_rho = XMLString::transcode("rho");
    ATTR_capacity = XMLString::transcode("capacity");

    m_ConfigFileParser = new XercesDOMParser;
}

/**
 *  Class destructor frees memory used to hold the XML tag and 
 *  attribute definitions. It als terminates use of the xerces-C
 *  framework.
 */

VesselConfig::~VesselConfig()
{
    // Free memory
    
    delete m_ConfigFileParser;
    try
    {
        XMLString::release( &TAG_root );
        
        XMLString::release( &TAG_General );
        XMLString::release( &TAG_Physics );
        XMLString::release( &TAG_Engine );
        XMLString::release( &TAG_Tank );
        
        // General
        XMLString::release( &ATTR_name );
        
        // Physics
        XMLString::release( &ATTR_mass );
        XMLString::release( &ATTR_Ixx );
        XMLString::release( &ATTR_Iyy );
        XMLString::release( &ATTR_Izz );
        XMLString::release( &ATTR_Ixy );
        XMLString::release( &ATTR_Ixz );
        XMLString::release( &ATTR_Iyz );
        
        // Engine
        XMLString::release( &ATTR_type );
        XMLString::release( &ATTR_mass_flow );
        
        // Tank
        XMLString::release( &ATTR_rho );
        XMLString::release( &ATTR_capacity );
    }
    catch( ... )
    {
        std::cerr << "Unknown exception encountered in TagNamesdtor" << std::endl;
    }
    
    // Terminate Xerces
    
    try
    {
        XMLPlatformUtils::Terminate();  // Terminate after release of memory
    }
    catch( xercesc::XMLException& e )
    {
        char* message = xercesc::XMLString::transcode( e.getMessage() );
        
        std::cerr << "XML ttolkit teardown error: " << message << std::endl;
        XMLString::release( &message );
    }
}

/**
 *  This function:
 *  - Tests the access and availability of the XML configuration file.
 *  - Configures the xerces-c DOM parser.
 *  - Reads and extracts the pertinent information from the XML config file.
 *
 *  @param in configFile The text string name of the HLA configuration file.
 */

void VesselConfig::readConfigFile(std::string& configFile)
throw( std::runtime_error )
{
    // Test to see if the file is ok.
    
    struct stat fileStatus;
    
    int iretStat = stat(configFile.c_str(), &fileStatus);
    if( iretStat == ENOENT )
        throw ( std::runtime_error("Path file_name does not exist, or path is an empty string.") );
    else if( iretStat == ENOTDIR )
        throw ( std::runtime_error("A component of the path is not a directory."));
    else if( iretStat == ELOOP )
        throw ( std::runtime_error("Too many symbolic links encountered while traversing the path."));
    else if( iretStat == EACCES )
        throw ( std::runtime_error("Permission denied."));
    else if( iretStat == ENAMETOOLONG )
        throw ( std::runtime_error("File can not be read\n"));
    
    // Configure DOM parser.
    
    m_ConfigFileParser->setValidationScheme( XercesDOMParser::Val_Never );
    m_ConfigFileParser->setDoNamespaces( false );
    m_ConfigFileParser->setDoSchema( false );
    m_ConfigFileParser->setLoadExternalDTD( false );
    
    try
    {
        m_ConfigFileParser->parse( configFile.c_str() );
        
        // no need to free this pointer - owned by the parent parser object
        DOMDocument* xmlDoc = m_ConfigFileParser->getDocument();
        
        // Get the top-level element: Name is "root". No attributes for "root"
        
        DOMElement* elementRoot = xmlDoc->getDocumentElement();
        if( !elementRoot ) throw(std::runtime_error( "empty XML document" ));
        
        // Parse XML file for tags of interest: "ApplicationSettings"
        // Look one level nested within "root". (child of root)
        
        DOMNodeList* children = elementRoot->getChildNodes();
        const  XMLSize_t nodeCount = children->getLength();
        
        // For all nodes, children of "root" in the XML tree.
        for( XMLSize_t xx = 0; xx < nodeCount; ++xx )
        {
            DOMNode* currentNode = children->item(xx);
            if( currentNode->getNodeType() && currentNode->getNodeType() == DOMNode::ELEMENT_NODE )
            {
                // Found node which is an Element. Re-cast node as element
                DOMElement* currentElement = dynamic_cast< xercesc::DOMElement* >( currentNode );
                // General section
                if( XMLString::equals(currentElement->getTagName(), TAG_General)) {
                    const XMLCh* xmlch_name = currentElement->getAttribute(ATTR_name);
                    name = std::string(XMLString::transcode(xmlch_name));
                    
                    const XMLCh* xmlch_model = currentElement->getAttribute(ATTR_model);
                    model = std::string(XMLString::transcode(xmlch_model));
                }
                
                // Physics section
                if( XMLString::equals(currentElement->getTagName(), TAG_Physics)) {
                    const XMLCh* xmlch_mass = currentElement->getAttribute(ATTR_mass);
                    mass = atof(XMLString::transcode(xmlch_mass));
                    
                    const XMLCh* xmlch_Ixx = currentElement->getAttribute(ATTR_Ixx);
                    Ixx = atof(XMLString::transcode(xmlch_Ixx));
                    
                    const XMLCh* xmlch_Iyy = currentElement->getAttribute(ATTR_Iyy);
                    Iyy = atof(XMLString::transcode(xmlch_Iyy));
                    
                    const XMLCh* xmlch_Izz = currentElement->getAttribute(ATTR_Izz);
                    Izz = atof(XMLString::transcode(xmlch_Izz));
                    
                    const XMLCh* xmlch_Ixy = currentElement->getAttribute(ATTR_Ixy);
                    Ixy = atof(XMLString::transcode(xmlch_Ixy));
                    
                    const XMLCh* xmlch_Ixz = currentElement->getAttribute(ATTR_Ixz);
                    Ixz = atof(XMLString::transcode(xmlch_Ixz));
                    
                    const XMLCh* xmlch_Iyz = currentElement->getAttribute(ATTR_Iyz);
                    Iyz = atof(XMLString::transcode(xmlch_Iyz));
                }
                
                // Engine section
                if( XMLString::equals(currentElement->getTagName(), TAG_Engine)) {
                    const XMLCh* xmlch_type = currentElement->getAttribute(ATTR_type);
                    type = from_string(XMLString::transcode(xmlch_type));
                    
                    const XMLCh* xmlch_mass_flow = currentElement->getAttribute(ATTR_mass_flow);
                    mass_flow = atof(XMLString::transcode(xmlch_mass_flow));
                }
                
                // Tank section
                if( XMLString::equals(currentElement->getTagName(), TAG_Tank)) {
                    const XMLCh* xmlch_rho = currentElement->getAttribute(ATTR_rho);
                    rho = atof(XMLString::transcode(xmlch_rho));
                    
                    const XMLCh* xmlch_capacity = currentElement->getAttribute(ATTR_capacity);
                    capacity = atof(XMLString::transcode(xmlch_capacity));
                }
            }
        }
    }
    catch( xercesc::XMLException& e )
    {
        char* message = xercesc::XMLString::transcode( e.getMessage() );
        std::ostringstream errBuf;
        errBuf << "Error parsing file: " << message << std::flush;
        XMLString::release( &message );
    }
}

Vessel* VesselConfig::getVessel(World& wd) {
    return wd.createVessel(name, model);
}

#ifdef MAIN_TEST
/* This main is provided for unit test of the class. */

int main(int argc, char** argv) {
    std::string configFile="/Users/ydethe/config.xml"; // stat file. Get ambigious segfault otherwise.
    
    VesselConfig appConfig;
    
    appConfig.readConfigFile(configFile);
    
    cout << "Application option A="  << appConfig.name  << endl;
    
    return 0;
}
#endif
