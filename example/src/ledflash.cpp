#include <iostream>
#include <getopt.h>

#include <udevpp.hpp>

#include <thread>
#include <chrono>

void print_usage()
{
	std::cout << "udevpp_ledflash ledflash <sysfs path to LED>" << std::endl;
	std::cout << std::endl;
	std::cout << "This will flash an sysft LED 10 times, then exit." << std::endl;
	std::cout << std::endl;
	std::cout << "Example: udevpp_ledflash /sys/class/leds/tpacpi\\:\\:power" << std::endl;
	
}

int main(int argc, char **argv)
{
	std::cout << "Udevpp led flash example" << std::endl;
	
	Udev::Udev udev;
	
	if (argc != 2)
	{
		print_usage();
		return -1;
	}
	
	Udev::UdevDevice device = udev.device_from_syspath(argv[1]);
	
	
	if (!device.has_sysattr("brightness"))
	{
		std::cerr << "Device does not have a brightness. It may not be an LED device." << std::endl;
		return -1;
	}
	
	std::string max_brightness = "1";
	
	if (device.has_sysattr("max_brightness"))
	{
		max_brightness = device.get_sysattr("max_brightness");
	}
	else
	{
		std::cout << "Device does not have a max_brightness? Assuming 1" << std::endl;
	}
	
	for (int x=0; x<10; x++) 
	{
		
		std::cout << "brightness: 0" << std::endl;
		device.set_sysattr("brightness", "0");
		std::this_thread::sleep_for (std::chrono::milliseconds(200));
		
		std::cout << "brightness: " << max_brightness << std::endl;
		device.set_sysattr("brightness", max_brightness);
		std::this_thread::sleep_for (std::chrono::milliseconds(200));
	}

	return 0;
}
