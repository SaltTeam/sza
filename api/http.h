#pragma once

#include "net.h"
#include <map>
#include <string>

namespace zia::api
{
    /**
    * Base class for requests and responses.
    */
    struct HttpMessage
    {
        enum class Version
        {
            unknown = 0,
            http_0_9 = 1,
            http_1_0 = 2,
            http_1_1 = 3,
            http_2_0 = 4
        };

        Version version;
        std::map<std::string, std::string> headers;
        Net::Raw body;

        HttpMessage() : version{Version::unknown}, headers{}, body{} {}
        virtual ~HttpMessage() = default;
    };

    struct HttpRequest : public HttpMessage
    {
        enum class Method
        {
            unknown = 0,
            options = 1,
            get = 2,
            head = 3,
            post = 4,
            put = 5,
            delete_ = 6,
            trace = 7,
            connect = 8
        };

        Method method;
        std::string uri;

        HttpRequest() : HttpMessage(), method{Method::unknown}, uri{} {}
        ~HttpRequest() override = default;
    };

    struct HttpResponse : public HttpMessage
    {
        enum class Status
        {
            unknown,
            continue_ = 100,
            switching_protocols = 101,
            ok = 200,
            created = 201,
            accepted = 202,
            nonauthoritative_information = 203,
            no_content = 204,
            reset_content = 205,
            partial_content = 206,
            multiple_choices = 300,
            moved_permanently = 301,
            found = 302,
            see_other = 303,
            not_modified = 304,
            use_proxy = 305,
            temporary_redirect = 307,
            bad_request = 400,
            unauthorized = 401,
            payment_required = 402,
            forbidden = 403,
            not_found = 404,
            method_not_allowed = 405,
            not_acceptable = 406,
            proxy_authentication_required = 407,
            request_timeout = 408,
            conflict = 409,
            gone = 410,
            length_required = 411,
            precondition_failed = 412,
            request_entity_too_large = 413,
            request_uri_too_large = 414,
            unsupported_media_type = 415,
            requested_range_not_satisfiable = 416,
            expectation_failed = 417,
            internal_server_error = 500,
            not_implemented = 501,
            bad_gateway = 502,
            service_unavailable = 503,
            gateway_timeout = 504,
            http_version_not_supported = 505
        };

        Status status;

        HttpResponse() : HttpMessage(), status{Status::unknown} {}
        ~HttpResponse() override = default;
    };

    /**
    * Represents a request and its response during pipeline processing.
    */
    struct HttpDuplex
    {
        NetInfo info;
        HttpRequest req;
        HttpResponse resp;

        HttpDuplex() = default;
        virtual ~HttpDuplex() = default;
    };
}
