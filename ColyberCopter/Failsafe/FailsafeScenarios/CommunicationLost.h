/**
 * @file CommunicationLost.h
 * @author your name (you@domain.com)
 * @brief Failsafe scenario that take action when communication is lost.
 * @date 2020-09-01
 * 
 */

#ifndef COMMUNICATIONLOST_H
#define COMMUNICATIONLOST_H

#include <IExecutable.h>
// TODO: create way to disarm motors, this something have to consider different motors configuration


class CommunicationLost : public IExecutable
{ // TODO: implement CommunicationLost failsafe class.
public:
    CommunicationLost();
    void execute() override;

private:
    bool getCommunicationState();
};


#endif
