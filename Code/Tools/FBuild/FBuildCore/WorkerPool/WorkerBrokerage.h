// WorkerBrokerage - Manage worker discovery
//------------------------------------------------------------------------------
#pragma once

// Includes
//------------------------------------------------------------------------------
#include "Core/Strings/AString.h"
#include "Core/Time/Timer.h"

// Forward Declarations
//------------------------------------------------------------------------------
class WorkerConnectionPool;
class ConnectionInfo;

// WorkerBrokerage
//------------------------------------------------------------------------------
class WorkerBrokerage
{
public:
    WorkerBrokerage();
    ~WorkerBrokerage();

    inline const Array<AString> & GetBrokerageRoots() const { return m_BrokerageRoots; }
    inline const AString & GetBrokerageRootPaths() const { return m_BrokerageRootPaths; }
    inline const AString & GetHostName() const { return m_HostName; }

    // client interface
    void FindWorkers( Array< AString > & workerList );
    void UpdateWorkerList( Array< uint32_t > &workerListUpdate );

    // server interface
    void SetAvailability( bool available );
private:
    void InitBrokerage();
    void UpdateBrokerageFilePath();

    bool ConnectToCoordinator();
    void DisconnectFromCoordinator();

    Array<AString>      m_BrokerageRoots;
    AString             m_BrokerageRootPaths;
    bool                m_Availability;
    bool                m_BrokerageInitialized;
    AString             m_HostName;
    AString             m_DomainName;
    AString             m_IPAddress;
    AString             m_BrokerageFilePath;
    Timer               m_TimerLastUpdate;      // Throttle network access
    Timer               m_TimerLastIPUpdate;    // Throttle dns access
    uint64_t            m_SettingsWriteTime;    // FileTime of settings time when last changed
    Timer               m_TimerLastCleanBroker;
    AString             m_CoordinatorAddress;
    WorkerConnectionPool * m_ConnectionPool;
    const ConnectionInfo * m_Connection;
    Array< uint32_t >   m_WorkerListUpdate;
    bool                m_WorkerListUpdateReady;
};

//------------------------------------------------------------------------------
