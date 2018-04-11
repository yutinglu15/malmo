
#include "MissionInitXML.h"
#include "XMLParseException.h"
// STL:
#include <exception>
#include <iostream>

// Boost:
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

namespace malmo {

    MissionInitXML::MissionInitXML(std::string xml_text) {
        parse(xml_text);
    }

    void MissionInitXML::parse(std::string xml_text) {

        boost::property_tree::ptree xml;

        std::istringstream is(xml_text);
        boost::property_tree::read_xml(is, xml);

        mission = xml.get_child("MissionInit.Mission");
        experiment_uid = xml.get<std::string>("MissionInit.ExperimentUID");
        minecraft_server.connection_address = xml.get_optional<std::string>("MissionInit.MincraftServerConnection.<xmlattr>.address");
        minecraft_server.connection_port = xml.get_optional<int>("MissionInit.MincraftServerConnection.<xmlattr>.port");
        client_role = xml.get<int>("MissionInit.ClientRole");
        schema_version = xml.get<std::string>("MissionInit.<xmlattr>.SchemaVersion");
        platform_version = xml.get<std::string>("MissionInit.<xmlattr>.PlatformVersion");

        client_agent_connection.client_ip_address = xml.get_optional<std::string>("MissionInit.ClientAgentConnection.ClientIPAddress").get_value_or("");
        client_agent_connection.client_mission_control_port = xml.get_optional<int>("MissionInit.ClientAgentConnection.ClientMissionControlPort").get_value_or(0);
        client_agent_connection.client_commands_port = xml.get_optional<int>("MissionInit.ClientAgentConnection.ClientCommandsPort").get_value_or(0);;
        client_agent_connection.agent_ip_address = xml.get_optional<std::string>("MissionInit.ClientAgentConnection.AgentIPAddress").get_value_or("");
        client_agent_connection.agent_mission_control_port = xml.get_optional<int>("MissionInit.ClientAgentConnection.AgentMissionControlPort").get_value_or(0);;
        client_agent_connection.agent_video_port = xml.get_optional<int>("MissionInit.ClientAgentConnection.AgentVideoPort").get_value_or(0);;
        client_agent_connection.agent_depth_port = xml.get_optional<int>("MissionInit.ClientAgentConnection.AgentDepthPort").get_value_or(0);;
        client_agent_connection.agent_lumunance_port = xml.get_optional<int>("MissionInit.ClientAgentConnection.AgentLuminancePort").get_value_or(0);;
        client_agent_connection.agent_observations_port = xml.get_optional<int>("MissionInit.ClientAgentConnection.AgentObservationsPort").get_value_or(0);;
        client_agent_connection.agent_rewards_port = xml.get_optional<int>("MissionInit.ClientAgentConnection.AgentRewardsPort").get_value_or(0);;
        client_agent_connection.agent_colour_map_port = xml.get_optional<int>("MissionInit.ClientAgentConnection.AgentColourMapPort").get_value_or(0);;
    }

    std::string MissionInitXML::toXml() const {
        std::ostringstream oss;

        boost::property_tree::ptree xml;
       
        xml.put("MissionInit.<xmlattr>.xmlns", "http://ProjectMalmo.microsoft.com");
        xml.put("MissionInit.<xmlattr>.xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
        xml.put<std::string>("MissionInit.<xmlattr>.SchemaVersion", schema_version);
        xml.put<std::string>("MissionInit.<xmlattr>.PlatformVersion", platform_version);
        xml.get_child("MissionInit").put_child("Mission", mission);
        xml.put<std::string>("MissionInit.ExperimentUID", experiment_uid);
        if (minecraft_server.connection_address)
            xml.put("MissionInit.MincraftServerConnection.<xmlattr>.address", minecraft_server.connection_address);
        if (minecraft_server.connection_port)
            xml.put("MissionInit.MincraftServerConnection.<xmlattr>.port", minecraft_server.connection_port);

        xml.put<int>("MissionInit.ClientRole", client_role);

        xml.put<std::string>("MissionInit.ClientAgentConnection.ClientIPAddress", client_agent_connection.client_ip_address);
        xml.put<int>("MissionInit.ClientAgentConnection.ClientMissionControlPort", client_agent_connection.client_mission_control_port);
        xml.put<int>("MissionInit.ClientAgentConnection.ClientCommandsPort", client_agent_connection.client_commands_port);
        xml.put<std::string>("MissionInit.ClientAgentConnection.AgentIPAddress", client_agent_connection.agent_ip_address);

        xml.put<int>("MissionInit.ClientAgentConnection.AgentMissionControlPort", client_agent_connection.agent_mission_control_port);
        xml.put<int>("MissionInit.ClientAgentConnection.AgentVideoPort", client_agent_connection.agent_video_port);
        xml.put<int>("MissionInit.ClientAgentConnection.AgentDepthPort", client_agent_connection.agent_depth_port);
        xml.put<int>("MissionInit.ClientAgentConnection.AgentLuminancePort", client_agent_connection.agent_lumunance_port);
        xml.put<int>("MissionInit.ClientAgentConnection.AgentObservationsPort", client_agent_connection.agent_observations_port);
        xml.put<int>("MissionInit.ClientAgentConnection.AgentRewardsPort", client_agent_connection.agent_rewards_port);
        xml.put<int>("MissionInit.ClientAgentConnection.AgentColourMapPort", client_agent_connection.agent_colour_map_port);

        write_xml(oss, xml);

        std::string xml_str = oss.str();
        xml_str.erase(std::remove(xml_str.begin(), xml_str.end(), '\n'), xml_str.end());

        std::cout << "------ toXML mission init -----" << std::endl;
        std::cout << xml_str << std::endl;

        return xml_str;
    }
}
