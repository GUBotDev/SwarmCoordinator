#include "DecisionHandler.h"

Node DecisionHandler::node;
//bool DecisionHandler::initComp = false;

void DecisionHandler::setBeacons(float* x, float* y, std::string* ID, int numBeacons){
	node.setBeacons(x, y, ID, numBeacons);
	beaconsInitialized = true;
}

void DecisionHandler::move(float x, float y){
	if (initComp && beaconsInitialized){
		std::pair<float, float> tempPos = node.returnXY();
		node.moveToPosition(x, y, tempPos.first, tempPos.second);
		node.checkTolerances(x, y, tempPos.first, tempPos.second);
	}
	else{
		node.initialize();
		node.requestBeacons();
	}
}

void DecisionHandler::turn(float targetDirection){
	if (initComp && beaconsInitialized){
		node.turnTo(targetDirection);
		node.checkTolerances(targetDirection);
	}
	else{
		node.initialize();
		node.requestBeacons();
	}
}

void DecisionHandler::localize(int num, float direction, std::string macOne, std::string macTwo){
	if (initComp && beaconsInitialized){
		switch(num){
			case 1:
				node.locateOne();
				break;
			case 2:
				node.locateTwo(direction);
				break;
			case 3:
				node.locateThree(macOne, macTwo, direction);
				break;
		}
	}
	else{
		node.initialize();
		node.requestBeacons();
	}
}

void DecisionHandler::initialize(){
	node.initialize();
}

void DecisionHandler::initComplete(){
	initComp = true;
}

bool DecisionHandler::isInit(){
	return initComp;
}

void DecisionHandler::alreadyInitialized(){
	node.alreadyInitialized();
}

void DecisionHandler::sendPosDir(){
	node.sendLastPositionDirection();
}

void DecisionHandler::unknownCommand(std::string data){
	node.unknownCommand(data);
}


