//
//  MCBCallLambda.h
//
//  Created by Radif Sharafullin on 22/02/13.
//
//
#ifndef __MCBPlatformSupport__MCBCallLambda__
#define __MCBPlatformSupport__MCBCallLambda__

#include "cocos2d.h"

namespace MCBPlatformSupport {
    class MCBCallLambda : public cocos2d::CCActionInstant{
        typedef cocos2d::CCActionInstant super;
        std::function<void()> _lambda=nullptr;
        virtual void update(float time) {execute();}
    public:
        static MCBCallLambda * create(std::function<void()> lambda);
        static cocos2d::CCSequence * createWithDelay(float delay, std::function<void()> lambda);
        virtual bool initWithLambda(const std::function<void()> & lambda);
        virtual void execute();
    protected:
        MCBCallLambda(){}
        virtual ~MCBCallLambda(){}
    };
    
    template <typename T>
    class MCBScheduleLambda : public cocos2d::CCActionInstant{
        typedef cocos2d::CCActionInstant super;
        std::function<void(float deltaTime, T *userData , bool & stop)> _lambda=nullptr;
        virtual void update(float deltaTime) {execute(deltaTime);}
        bool _isDone=false;
        virtual bool isDone(){return _isDone;}
        virtual void step(float dt){update(dt);}
        T _userData;
    public:
        static MCBScheduleLambda * create(T userData, std::function<void(float deltaTime, T *userData , bool & stop)> lambda){
            MCBScheduleLambda *pRet = new MCBScheduleLambda();
            if (pRet){
                pRet->_lambda=std::move(lambda);
                pRet->_userData=std::move(userData);
                pRet->autorelease();
                return pRet;
            }
            CC_SAFE_DELETE(pRet);
            return nullptr;
        }
        virtual void execute(float deltaTime){
            if (_lambda)
                _lambda(deltaTime, &_userData,_isDone);
        }
    protected:
        MCBScheduleLambda(){}
        virtual ~MCBScheduleLambda(){}
    };
    
}


#endif /* defined(__MCBPlatformSupport__MCBCallLambda__) */
