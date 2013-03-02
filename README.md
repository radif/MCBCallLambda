MCBCallLambda
=============

Cocos2dx CCCallFunc like action that takes c++11 lambda.<br>
<br>

        auto callLater(MCBPlatformSupport::MCBCallLambda::create([=](){
                doSomethingWithCapturedParameters(s);
            }));
	
        runAction(CCSequence::createWithTwoActions(CCDelayTime::create(.5f), callLater));
<br>

Update1: added the factory for the sequence (createWithDelay), which can save lots of typing dealing with CCSequences

captured variable is s:

	runAction(MCBPlatformSupport::MCBCallLambda::createWithDelay(1.f,[=](){
	        playWelcome(s);
	        s->doWelcomeAnimation();
        	//calling another action from the first one with delay
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


anonymous example (no user data persists)

	runAction(MCBPlatformSupport::create_scheduleLambda(nullptr,[=](float deltaTime, void *, bool & stop){
		
		//------------example update work begins
	        static float radius=.0f;
	        static float angle=.0f;
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
	        //------------update work ends
	        
	    }));


float example

	runAction(MCBPlatformSupport::create_scheduleLambda(0.0f,[=](float deltaTime, float *radius, bool & stop){
		//get the data from the pointer
	        float rad=*radius;

		//------------example update work begins
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
	        //------------update work ends

		//persist the data to the pointer
	        *radius=rad;
	    }));


struct example

	 struct radAngle {float radius=.0f;float angle=.0f;};

	    runAction(MCBPlatformSupport::create_scheduleLambda(radAngle(),[=](float deltaTime, radAngle *data, bool & stop){
	        //get the data from the struct pointer
	        float radius(data->radius);
	        float angle(data->angle);
	        
	        //------------example update work begins
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
	        //------------update work ends

		//persist the data back to the struct pointer
	        data->angle=angle;
	        data->radius=radius;

	    }));
