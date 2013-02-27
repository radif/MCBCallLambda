//
//  MCBCallLambda.h
//  MCBAnimationEngine
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
        virtual bool initWithLambda(const std::function<void()> & lambda);
        virtual void execute();
    protected:
        MCBCallLambda(){}
        virtual ~MCBCallLambda(){}
    };

}


#endif /* defined(__MCBPlatformSupport__MCBCallLambda__) */
