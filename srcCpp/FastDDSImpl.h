/*
 * (c) 2005-2020  Copyright, Real-Time Innovations, Inc. All rights reserved.
 * Subject to Eclipse Public License v1.0; see LICENSE.md for details.
 */

#ifndef __FASTDDSIMPL_H__
#define __FASTDDSIMPL_H__

#ifdef EPROSIMA_PERF_FASTDDS

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

    #define RTIPERFTEST_MAX_PEERS 1024

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

    const std::string get_qos_profile_name(const char *topicName);

protected:

    // Perftest related entities
    perftest_cpp *_parent;
    ParameterManager *_PM;
    PerftestSemaphore *_pongSemaphore;
    std::map<std::string, std::string> _qoSProfileNameMap;

    // DDS Entities
    eprosima::fastdds::dds::DomainParticipantFactory *_factory;
    eprosima::fastdds::dds::DomainParticipant *_participant;
    eprosima::fastdds::dds::Publisher *_publisher;
    eprosima::fastdds::dds::Subscriber *_subscriber;
    eprosima::fastdds::dds::TypeSupport _type; //This is a std::shared_ptr
};

#endif // EPROSIMA_PERF_FASTDDS
#endif // __FASTDDSIMPL_H__
