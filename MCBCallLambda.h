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
    
    class MCBScheduleLambda : public cocos2d::CCActionInstant{
        typedef cocos2d::CCActionInstant super;
        std::function<void(float deltaTime, bool & stop)> _lambda=nullptr;
        virtual void update(float deltaTime) {execute(deltaTime);}
        bool _isDone=false;
        virtual bool isDone(){return _isDone;}
        virtual void step(float dt){update(dt);}
    public:
        static MCBScheduleLambda * create(std::function<void(float deltaTime, bool & stop)> lambda);
        static cocos2d::CCSequence * createWithDelay(float delay, std::function<void(float deltaTime, bool & stop)> lambda);
        virtual bool initWithLambda(const std::function<void(float deltaTime, bool & stop)> & lambda);
        virtual void execute(float deltaTime);
    protected:
        MCBScheduleLambda(){}
        virtual ~MCBScheduleLambda(){}
    };
    
}


#endif /* defined(__MCBPlatformSupport__MCBCallLambda__) */
