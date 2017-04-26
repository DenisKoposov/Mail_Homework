#include "error_codes.hpp"

const char* xmpp_error::xmpp_category_impl::name() const noexcept
{
    return "xmpp";
}

std::string xmpp_error::xmpp_category_impl::message( int ev ) const noexcept
{
    xmpp_error_t err = static_cast<xmpp_error_t>( ev );
    switch ( err )
    {
    case xmpp_error_t::ok:
        return "OK";

    case xmpp_error_t::redirect:
        return "Redirect";

    case xmpp_error_t::bad_request:
        return "Bad request";

    case xmpp_error_t::not_authorized:
        return "Not authorized";

    case xmpp_error_t::payment_required:
        return "Payment required";

    case xmpp_error_t::forbidden:
        return "Forbidden";

    case xmpp_error_t::item_not_found:
        return "Item not found";

    case xmpp_error_t::not_allowed:
        return "Not allowed";

    case xmpp_error_t::not_acceptable:
        return "Not acceptable";

    case xmpp_error_t::registration_required:
        return "Registration required";

    case xmpp_error_t::conflict:
        return "Conflict";

    case xmpp_error_t::feature_not_implemented:
        return "Feature not implemented";

    case xmpp_error_t::service_unavailable:
        return "Service unavailable";

    case xmpp_error_t::internal_server_error:
        return "Internal server error";

    case xmpp_error_t::remote_server_timeout:
        return "Remote server timeout";

    default:
        return "Unknown XMPP error";
    }
}

const std::error_category& xmpp_category()
{
    static xmpp_error::xmpp_category_impl xmpp_category_instance;
    return xmpp_category_instance;
}

std::error_code xmpp_error::make_error_code( xmpp_error_t e )
{
    return std::error_code( static_cast<int>( e ),
    xmpp_category() );
}

std::error_condition xmpp_error::make_error_condition( xmpp_error_t e )
{
    return std::error_condition( static_cast<int>( e ),
    xmpp_category() );
}
