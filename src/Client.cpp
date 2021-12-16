//
// Created by toni on 03/12/21.
//

#include "../includes/Client.h"

Client::~Client() {
    for (Ticket *t : _tickets)
        t->setClient(nullptr);
}
