#include "Node.h"

std::string Node::getName(){
	return name;
}

void Node::handleInput(std::string data){

}

void Node::setBeacon(bool hasBeacon){
	this->hasBeacon = hasBeacon;
}

void Node::setBusy(bool isBusy){
	this->isBusy = isBusy;
}

void Node::setName(std::string name){
	this->name = name;
}
