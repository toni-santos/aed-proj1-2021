#include "../includes/Client.h"

Client::~Client() {
    for (Ticket *t : _tickets)
        t->setClient(nullptr);
}

void Client::removeTicket(Ticket *ticket) {
    if (ticket) {
        ticket->setClient(nullptr);
        for (auto it{_tickets.begin()}, end{_tickets.end()}; it < end; ++it)
            if (*it == ticket)
                _tickets.erase(it);
    }
}
