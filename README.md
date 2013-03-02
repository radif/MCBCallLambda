MCBCallLambda
=============

Cocos2dx CCCallFunc like action that takes c++11 lambda.<br>
<br>

        auto callLater(MCBPlatformSupport::MCBCallLambda::create([=](){
                doSomethingWithCapturedParameters(s);
            }));
<br>

        runAction(CCSequence::createWithTwoActions(CCDelayTime::create(.5f), callLater));
<br>
Update1: added the factory for the sequence (createWithDelay)

captured variable is s:

	runAction(MCBPlatformSupport::MCBCallLambda::createWithDelay(1.f,[=](){
	        playWelcome(s);
	        s->doWelcomeAnimation();
        
	        runAction(MCBPlatformSupport::MCBCallLambda::createWithDelay(1.f,[=](){
	            triggerIntroAnimation(s);
            
	            runAction(MCBPlatformSupport::MCBCallLambda::createWithDelay(1.f, [=](){
	                s->animateCredits();
	                runAction(MCBPlatformSupport::MCBCallLambda::createWithDelay(.5f, [=](){
	                    removeChild(s, true);
	                    setInteractionEnabled(true);
	                }));
                
	            }));
            
	        }));
        
	    }));
	    
	    
Update2: added MCBScheduleLambda<T> for scheduling updates with captured variables, which is good for animating shader values
<br>

anonymous example (no user data persists)

	runAction(MCBPlatformSupport::MCBScheduleLambda<void *>::create(nullptr,[=](float dt, void *, bool & stop){
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


float example

	runAction(cdaPlatformSupport::cdaScheduleLambda<float>::create(0.0f,[=](float dt, float *radius, bool & stop){
	        float rad=*radius;

	        if ( _shaderData.bothPointsInvalid()){
	            _shaderData.resetAttractionPoints();
	            rad=0;
	        }
	        rad+=dt*1.5f;
	        if (rad>.4)
	            stop=true;

	        _shaderData.touch1Position.x=sinf(angle)*rad+.5f;
	        _shaderData.touch1Position.y=cosf(angle)*rad+.5f;

	        _shaderData.touch2Position.x=sinf(PI-angle)*rad+.5f;
	        _shaderData.touch2Position.y=cosf(PI-angle)*rad+.5f;

	        *radius=rad;
	    }));


struct example

	 struct radAngle {float radius=.0f;float angle=.0f;};

	    runAction(cdaPlatformSupport::cdaScheduleLambda<radAngle>::create(radAngle(),[=](float dt, radAngle *data, bool & stop){
	        float radius(data->radius);
	        float angle(data->angle);
	        if ( _shaderData.bothPointsInvalid()){
	            _shaderData.resetAttractionPoints();
	            radius=0;
	            angle=0;
	        }
	        radius+=dt*1.5f;
	        angle+=dt*.15f;

	        _shaderData.touch1Position.x=sinf(angle)*radius+.5f;
	        _shaderData.touch1Position.y=cosf(angle)*radius+.5f;

	        _shaderData.touch2Position.x=sinf(PI-angle)*radius+.5f;
	        _shaderData.touch2Position.y=cosf(PI-angle)*radius+.5f;

	        data->angle=angle;
	        data->radius=radius;

	    }));
