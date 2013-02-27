//
//  MCBCallLambda.cpp
//  MCBPlatformSupport
//
//  Created by Radif Sharafullin on 22/02/13.
//
//

#include "MCBCallLambda.h"

namespace MCBPlatformSupport {
    void MCBCallLambda::execute(){
        if (_lambda)
            _lambda();
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
}
