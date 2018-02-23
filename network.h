/*
 * This file cotains the network routines
 * and data about current interfaces, along with
 * the functions to push and pull data from the blockchain
 * network.
 *
 * Author: sandesh Bhusal.
 *
 */
#ifndef GTKMMPROJECT_NETWORK_H
#define GTKMMPROJECT_NETWORK_H
#include <iostream>
#include <vector>
#include <thread>
#include <string>
#include <cstdio>
#include <cctype>
#include <cstring>
#include "arpa/inet.h"
#include "ui.h"
#include "resources.h"
#include <ifaddrs.h>
#include <bits/stdc++.h>
#include <netdb.h>

const int udpListenPort   = 8888;
const int tcpTransferPort = 7777;
sockaddr_in inputStation;
int udpListenSocket;

int tcpTransferSocket;
bool firstRun = true;
std::set<std::map<std::string, std::string> > alivePeers; // IP and Name
void errorMessage(std::string err){
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                               GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK_CANCEL, err.c_str());
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(GTK_WIDGET(dialog));
}
void infoMessage(std::string err){
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                               GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK_CANCEL, err.c_str());
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(GTK_WIDGET(dialog));
}
std::thread *broadcastListener;

std::thread *messageListener;

class Network{
private:
    typedef struct sockaddr_in  station;
    typedef struct sockaddr     stationBase;
public:
    Network(){
        if(firstRun){
            int accessTrigger = 1;
            udpListenSocket   = socket(AF_INET, SOCK_DGRAM,  IPPROTO_UDP);
            tcpTransferSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            setsockopt(udpListenSocket, SOL_SOCKET, SO_BROADCAST, &accessTrigger, sizeof(accessTrigger));
            setsockopt(udpListenSocket, SOL_SOCKET, SO_REUSEADDR, &accessTrigger, sizeof(accessTrigger));
            setsockopt(tcpTransferSocket, SOL_SOCKET, SO_REUSEADDR, &accessTrigger, sizeof(accessTrigger));
            std::string handshake = "c|bhusal";
            broadcastAvailability(true, handshake);
            bindBroadcastPort();
            broadcastListener = new std::thread(listenPeerBroadcast);
            bindMessagePort();
            messageListener   = new std::thread(listenMessage);
        }
    }
    static char* getChars(const std::string &input){
        auto retVal = new char[input.length()];
        strcpy(retVal, input.c_str());
        return retVal;
    }
    static void  broadcastAvailability(bool available, std::string &handshake){
        if(available){
            std::cout << "Broadcasting availability as "<< available <<" to peers..." << std::endl;

            station motherShip ;
            memset(&motherShip, 0, sizeof(motherShip));

            motherShip.sin_port         = htons(udpListenPort);
            motherShip.sin_family       = AF_INET;
            motherShip.sin_addr.s_addr  = inet_addr("255.255.255.255");

            int pings = 5;
            while(pings--){
                if(sendto(udpListenSocket, getChars(handshake), strlen(getChars(handshake)), 0, (stationBase*)&motherShip, sizeof(station))== -1){
                    std::cout << "Could not broadcast address. Retrying for another "<< pings <<" attempts" << std::endl;
                }
                else{
                    std::cout << "Successfully broadcast!" << std::endl;
                    return;
                }
            }
            std::cout << "Failed to broadcast. Are you connected?" << std::endl;
        }
        else{
            std::string sendMsg = "disconnected";
            broadcastAvailability(true, sendMsg);
        }
    }
    static bool  bindBroadcastPort(){
        udpListenSocket   = socket(AF_INET, SOCK_DGRAM,  IPPROTO_UDP);

        station me;
        memset(&me, 0, sizeof(me));
        me.sin_port = htons(udpListenPort);
        me.sin_family = AF_INET;
        me.sin_addr.s_addr = INADDR_ANY;

        if(bind(udpListenSocket, (stationBase*)&me, sizeof(me)) == -1){
            std::cout << "Could not bind to interface for listening to broadcasts. " << std::endl;
            return false;
        }
        else{
            std::cout << "Successfully bound to UDP port to listen to broadcasts. " << std::endl;
            return true;
        }
    }
    static bool  bindMessagePort(){
        inputStation.sin_family      = AF_INET;
        inputStation.sin_addr.s_addr = INADDR_ANY;
        inputStation.sin_port        = htons(tcpTransferPort);
        class bindException{};
        class listenException{};
        try{
            int out = bind(tcpTransferSocket, (stationBase *)&inputStation, sizeof(inputStation));
            if(out<0)
                throw new bindException;
            int x = listen(tcpTransferSocket, 3);
            if(x < 0)
                throw new listenException;
        }
        catch(bindException e) {
            g_print("Could not bind to 192.168.1.1");
            return false;
        }
        catch(listenException e){
            g_print("Could not listen to anything...");
            return false;
        }
        return true;
    }
    static void  listenPeerBroadcast(){
        station incoming;
        std::string incomingIP;
        std::string incomingName;
        char buffer[1024];
        unsigned int len = sizeof(station);
        g_print("Listening who is getting connected\n");
        auto readBytes = recvfrom(udpListenSocket, buffer, 1024, 0, (stationBase *)&incoming, &len);
        if(readBytes > 0){
            if(buffer[0] == 'c'){
                incomingIP = inet_ntoa(incoming.sin_addr);
                std::string name;
                for(int i=2; i<readBytes-1; i++)
                    name[i-2] = buffer[i];
//                std::pair<std::string, std::string> x = std::make_pair(incomingIP, name);
//                std::map<std::string, std::string> m;
//                m.insert(x);
//                alivePeers.insert(m);
//                infoMessage(buffer);
            }
            else{
                g_print("%s ", inet_ntoa(incoming.sin_addr));
                for(int i=2; i<readBytes-1; i++)
                    g_print("%c", buffer[i]);
                populateActive(userListBox, "buffer");
            }
        }
    }
    static int   getInterfaceCount(){
        int inet = 0, inet6 = 0;
        struct ifaddrs *interfaces, *iterator;
        int family, s, n;
        if(getifaddrs(&interfaces) == -1){
            errorMessage("Could not bind connections!");
            return -1;
        }
        else{
            for(iterator = interfaces; iterator != NULL; iterator = iterator->ifa_next) {
                if(iterator->ifa_addr->sa_family == AF_INET){
                    inet++;
                }
                else if(iterator->ifa_addr->sa_family == AF_INET6){
                    inet6++;
                }
            }
            return inet;
        }
    }
    static void  listenMessage(){
        int *sendinStation = new int;
        int size = sizeof(station);
        g_print("listening connections\n");
        *sendinStation = accept(tcpTransferSocket, (stationBase*)&inputStation, (socklen_t*)&size);
        char buffer[1024];
        g_print("Got something...\n");
        while(true){
            read(*sendinStation, buffer, 1024);
            g_print("%s\n", buffer);
            addReceivedMessage(messageViewer, buffer);
        }
        const auto wait_duration = std::chrono::milliseconds(10);
        std::this_thread::sleep_for(wait_duration);
        messageListener = new std::thread(listenMessage);
    }
};
#endif