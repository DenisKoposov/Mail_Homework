#pragma once

#include <system_error>

namespace xmpp_error
{
    enum class xmpp_error_t
    {
        ok                      = 0,
        redirect                = 302,
        bad_request             = 400,
        not_authorized          = 401,
        payment_required        = 402,
        forbidden               = 403,
        item_not_found          = 404,
        not_allowed             = 405,
        not_acceptable          = 406,
        registration_required   = 407,
        conflict                = 409,
        feature_not_implemented = 501,
        service_unavailable     = 503,
        internal_server_error   = 500,
        remote_server_timeout   = 504
    };

    class xmpp_category_impl: public std::error_category
    {
    public:

        virtual const char* name() const noexcept;
        virtual std::string message( int ev ) const noexcept;
    };

    std::error_code make_error_code( xmpp_error_t e );
    std::error_condition make_error_condition( xmpp_error_t e );
}

const std::error_category& xmpp_category();

namespace std
{
    template <>
    struct is_error_code_enum<xmpp_error::xmpp_error_t>: public true_type {};
}
