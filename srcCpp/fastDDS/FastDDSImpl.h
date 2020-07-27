/*
 * (c) 2005-2020  Copyright, Real-Time Innovations, Inc. All rights reserved.
 * Subject to Eclipse Public License v1.0; see LICENSE.md for details.
 */

#ifndef __FASTDDSIMPL_H__
#define __FASTDDSIMPL_H__

#ifdef PERTEST_EPROSIMA_FASTDDS

#include "Infrastructure_common.h"
#include "MessagingIF.h"
#include "PerftestTransport.h"
#include <algorithm>
#include <map>
#include <stdexcept>  // This header is part of the error handling library.
#include <string>

// Files generated by the type
#include "perftest.h"
#include "perftestPubSubTypes.h"

// Fast DDS related classes
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/attributes/SubscriberAttributes.h>
#include <fastrtps/attributes/PublisherAttributes.h>
#include <fastdds/dds/domain/DomainParticipantListener.hpp>
#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/SampleInfo.hpp>
#include <fastdds/dds/subscriber/qos/DataReaderQos.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/DataWriterListener.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastrtps/xmlparser/XMLProfileManager.h>


using namespace eprosima::fastdds::dds;
using namespace eprosima::fastrtps::rtps;
using namespace eprosima::fastrtps;
using namespace eprosima::fastrtps::xmlparser;
using eprosima::fastrtps::PublisherAttributes;
using eprosima::fastrtps::SubscriberAttributes;

/* Forward declaration of perftest_cpp to avoid circular dependencies */
class perftest_cpp;

template <typename T>
class FastDDSImpl : public IMessaging
{

public:

    FastDDSImpl();

    ~FastDDSImpl()
    {
        Shutdown();
    }

    bool validate_input();

    std::string PrintConfiguration();

    bool Initialize(ParameterManager &PM, perftest_cpp *parent);

    void Shutdown();

    unsigned long GetInitializationSampleCount();

    IMessagingWriter *CreateWriter(const char *topic_name);

    /*
     * Pass null for callback if using IMessagingSubscriber.ReceiveMessage()
     * to get data
     */
    IMessagingReader *CreateReader(const char *topic_name, IMessagingCB *callback);

    bool supports_listener()
    {
        return true;
    };

    bool supports_discovery()
    {
        return true;
    };

    bool configure_participant_qos(DomainParticipantQos &qos);
    bool configure_writer_qos(DataWriterQos &qos, std::string qosProfile);
    bool configure_reader_qos(DataReaderQos &qos, std::string qosProfile);

    const std::string get_qos_profile_name(const char *topicName);

protected:

    // Perftest related entities
    perftest_cpp *_parent;
    ParameterManager *_PM;
    PerftestTransport _transport;
    PerftestSemaphore *_pongSemaphore;
    std::map<std::string, std::string> _qoSProfileNameMap;

    // DDS Entities
    eprosima::fastdds::dds::DomainParticipantFactory *_factory;
    eprosima::fastdds::dds::DomainParticipant *_participant;
    eprosima::fastdds::dds::Publisher *_publisher;
    eprosima::fastdds::dds::Subscriber *_subscriber;
    eprosima::fastdds::dds::TypeSupport _type; //This is a std::shared_ptr
};

#endif // PERTEST_EPROSIMA_FASTDDS
#endif // __FASTDDSIMPL_H__
