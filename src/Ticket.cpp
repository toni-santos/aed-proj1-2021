#include "../includes/Ticket.h"

Ticket::~Ticket() {
    if (_client) {
        _client->removeTicket(this);
    }
}
