#ifndef _TimeInterval_H__
#define _TimeInterval_H__

class TimeInterval {

	private:
		unsigned long previousMillis;
		unsigned long currentMillis;
		int interval;

	public:
		TimeInterval ();
		~TimeInterval ();
		void go();

};
 

#endif