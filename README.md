MCBCallLambda
=============

Cocos2dx CCCallFunc like action that takes c++11 lambda.<br>
<br>
auto callLater(MCBPlatformSupport::MCBCallLambda::create(\[=\](){<br>
        doSomethingWithCapturedParameters(s);<br>
    }));<br>
<br>
runAction(CCSequence::createWithTwoActions(CCDelayTime::create(.5f), callLater));
<br><br>
Update1: added the factory for the sequence (createWithDelay)
Update2: added MCBScheduleLambda for scheduling updates with captured variables, which is good for animating shader values
runAction(MCBPlatformSupport::MCBScheduleLambda::create([=](float dt, bool & stop){
        static float radius=.0f;
        static float angle=.0f;
        
        
        if ( _shaderData.bothPointsInvalid()){
            _shaderData.resetAttractionPoints();
            radius=0;
            angle=0;
        }
        CCLog("dt: %f",dt);
        radius+=dt*1.5f;
        angle+=dt*.15f;
        
        _shaderData.touch1Position.x=sinf(angle)*radius+.5f;
        _shaderData.touch1Position.y=cosf(angle)*radius+.5f;
        
        _shaderData.touch2Position.x=sinf(PI-angle)*radius+.5f;
        _shaderData.touch2Position.y=cosf(PI-angle)*radius+.5f;
    }));

