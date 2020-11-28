#pragma once
class vehicle
{
public:
	vehicle(int kmph_ = 60, int kmpl_ = 7): kmph(kmph_), kmpl(kmpl_) {}
	int kmph;
	int kmpl;
};