//
// Created by ANTONIO on 12/2/2021.
//

#include "../includes/Ticket.h"

Ticket::~Ticket() {
    if (_client) {
        _client->removeTicket(this);
    }
}
