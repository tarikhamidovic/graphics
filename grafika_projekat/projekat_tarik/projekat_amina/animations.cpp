#include"variables.cpp"

void translation(){
 if(translate){
		if(counter1<20 && counter2==0 &&path1%2!=0 &&path2%2!=0){
			if(!translate_state){
				translate_right-=0.1f;
				counter1++;
			}
			else if(translate_state){
			 translate_right-=0.3f;
			 counter1+=3;
			}
		}
		if(counter1<20 && counter2==0 && path1%2==0 &&path2%2!=0){
			if(!translate_state){
				translate_right+=0.1f;
				counter1++;
			}
			else if(translate_state){
			 translate_right+=0.3f;
			 counter1+=3;
			}
		}
		if(counter1>=20) {
			counter1=0;
			path1++;
		}
		if(counter2<20 && counter1==0 && path1%2==0 && path2%2==0){
			if(!translate_state){
				translate_left+=0.1f;
				counter2++;
			}
			else if(translate_state){
			 translate_left+=0.3f;
			 counter2+=3;
			}
		}
		if(counter2<20 && counter1==0 && path1%2==0 && path2%2!=0){
			if(!translate_state){
				translate_left-=0.1f;
				counter2++;
			}
			else if(translate_state){
			 translate_left-=0.3f;
			 counter2+=3;
			}

		}
		if(counter2>=20){
			counter2=0;
			path2++;
		}
	}
	std::this_thread::sleep_for (std::chrono::milliseconds(20));
}

void rotation(){
	if(rotate){
		if(rotate_state) angle+=9.0f;
		else
		angle+=1.0f;
	}
}

void scaling(){
	if(scale) {
		if(counter3<50 && path3%2==0){
		if(scaling_state) {
			factor+=0.03f;
			counter3+=3;
		}
		else {
			factor+=0.01f;
			counter3++;
		}
	}
	 if(counter3<50 && path3%2!=0){
	 	if(scaling_state) {
			factor-=0.03f;
			counter3+=3;
		}
		else {
			factor-=0.01f;
			counter3++;
		}
	 }
	 if(counter3>=50){
	 	counter3=0;
	 	path3++;
	 }

}
}