#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <string>
#include <vector>
#include <memory>

namespace zia::api
{
    /**
    * Represents an IPv4 address.
    */
    struct NetIp
    {
        std::uint32_t i;
        std::string str;
    };

    /**
    * Struct identifying socket (implementation-defined).
    */
    struct ImplSocket;

    /**
    * Infos on client.
    */
    struct NetInfo
    {
        std::chrono::system_clock::time_point time;
        std::chrono::steady_clock::time_point start;

        NetIp ip;
        std::uint16_t port;

        std::shared_ptr<ImplSocket> sock;

        NetInfo() : time{}, start{}, ip{}, port{}, sock{} {}
        virtual ~NetInfo() = default;
    };

    /**
    * Interface for multithreaded network abstraction.
    * Dynamic library implementing it must export a "create" C function returning a "Net*" (caller should use smart pointers).
    */
    class Net
    {
    public:
        /**
        * Type used to receive and send packets.
        */
        using Raw = std::string;

        /**
        * Type of callback called on request.
        */
        using Callback = std::function<void(Raw, NetInfo)>;

        Net() = default;

        virtual ~Net() = default;

        /**
        * Launch the server asynchronously, callback will be called when a request is received.
        * \return true on success, otherwise false
        */
        virtual bool run(Callback cb) = 0;

        /**
        * Send a response.
        * \return true on success, otherwise false
        */
        virtual bool send(std::shared_ptr<ImplSocket> sock, Raw resp) = 0;

        /**
        * Stop the server.
        * \return true on success, otherwise false
        */
        virtual bool stop() = 0;
    };
}
