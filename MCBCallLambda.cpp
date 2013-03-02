//
//  MCBCallLambda.cpp
//
//  Created by Radif Sharafullin on 22/02/13.
//
//

#include "MCBCallLambda.h"

namespace MCBPlatformSupport {
    
    //MCBCallLambda
    
    void MCBCallLambda::execute(){
        if (_lambda)
            _lambda();
    }
    cocos2d::CCSequence * MCBCallLambda::createWithDelay(float delay, std::function<void()> lambda){
        MCBCallLambda *pRet = new MCBCallLambda();
        if (pRet && pRet->initWithLambda(lambda)){
            pRet->autorelease();
            return cocos2d::CCSequence::createWithTwoActions(cocos2d::CCDelayTime::create(delay),pRet);
        }
        CC_SAFE_DELETE(pRet);
        return nullptr;
    }
    
    MCBCallLambda * MCBCallLambda::create(std::function<void()> lambda){
        MCBCallLambda *pRet = new MCBCallLambda();
        if (pRet && pRet->initWithLambda(lambda)){
            pRet->autorelease();
            return pRet;
        }
        CC_SAFE_DELETE(pRet);
        return nullptr;
    }
    bool MCBCallLambda::initWithLambda(const std::function<void()> & lambda){
        _lambda=std::move(lambda);
        return true;
    }
    
    
    
    //MCBScheduleLambda
    
    
    void MCBScheduleLambda::execute(float deltaTime){
        if (_lambda)
            _lambda(deltaTime, _isDone);
    }
    cocos2d::CCSequence * MCBScheduleLambda::createWithDelay(float delay, std::function<void(float deltaTime, bool & stop)> lambda){
        MCBScheduleLambda *pRet = new MCBScheduleLambda();
        if (pRet && pRet->initWithLambda(lambda)){
            pRet->autorelease();
            return cocos2d::CCSequence::createWithTwoActions(cocos2d::CCDelayTime::create(delay),pRet);
        }
        CC_SAFE_DELETE(pRet);
        return nullptr;
    }
    
    MCBScheduleLambda * MCBScheduleLambda::create(std::function<void(float deltaTime, bool & stop)> lambda){
        MCBScheduleLambda *pRet = new MCBScheduleLambda();
        if (pRet && pRet->initWithLambda(lambda)){
            pRet->autorelease();
            return pRet;
        }
        CC_SAFE_DELETE(pRet);
        return nullptr;
    }
    bool MCBScheduleLambda::initWithLambda(const std::function<void(float deltaTime, bool & stop)> & lambda){
        _lambda=std::move(lambda);
        return true;
    }
}
