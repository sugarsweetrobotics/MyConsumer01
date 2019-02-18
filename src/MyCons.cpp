// -*- C++ -*-
/*!
 * @file  MyCons.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "MyCons.h"

// Module specification
// <rtc-template block="module_spec">
static const char* mycons_spec[] =
  {
    "implementation_id", "MyCons",
    "type_name",         "MyCons",
    "description",       "ModuleDescription",
    "version",           "1.0.0",
    "vendor",            "VenderName",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
MyCons::MyCons(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_sv01Port("sv01")

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
MyCons::~MyCons()
{
}



RTC::ReturnCode_t MyCons::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  m_sv01Port.registerConsumer("ssr_ServiceExample", "ssr::ServiceExample", m_service);
  
  // Set CORBA Service Ports
  addPort(m_sv01Port);
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t MyCons::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t MyCons::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t MyCons::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t MyCons::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t MyCons::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t MyCons::onExecute(RTC::UniqueId ec_id)
{
	std::cout << "MyCons::onExecute ------------------" << std::endl;
	coil::usleep(1000 * 1000);

	std::cout << "Open File." << std::endl;;

	std::cout << "Raise Exception Test." << std::endl;
	try {
		std::cout << " - opening hogehoge.txt" << std::endl;
		m_service->open("hogehoge.txt");
		std::cout << " - open success (Test FAILURE)" << std::endl;
	}
	catch (ssr::ServiceExample::NoSuchFileError& ex) {
		std::cout << " - Success. Exception occurred: " << ex.message << std::endl;
	}

	long fp = -1;
	try {
		fp = m_service->open("foo.txt");
		std::cout << " - open success (Test SUCCESS)" << std::endl;
	}
	catch (ssr::ServiceExample::NoSuchFileError& ex) {
		std::cout << " - Failure. Exception occurred: " << ex.message << std::endl;
	}

	std::cout << "Write Test." << std::endl;

	coil::TimeMeasure clock;
	clock.tick();
	m_service->write(fp, 3456);
	clock.tack();
	coil::TimeValue val = clock.interval();

	std::cout << "-write takes : " << (double)val << " sec." << std::endl;

	long data = m_service->read(fp);

	std::cout << " - data is " << data << std::endl;
	if (data == 3456) std::cout << " -- success." << std::endl;
	else std::cout << " -- failure." << std::endl;

	clock.tick();
	m_service->fastwrite(fp, 7890);
	clock.tack();
	val = clock.interval();

	std::cout << "-write takes : " << (double)val << " sec." << std::endl;

	data = m_service->read(fp);

	std::cout << " - data is " << data << std::endl;
	if (data == 7890) std::cout << " -- success." << std::endl;
	else std::cout << " -- not raedy. but may written after 3 sec." << std::endl;

	std::cout << " - sleep(3 sec)" << std::endl;
	coil::usleep(3 * 1000 * 1000);

	data = m_service->read(fp);

	std::cout << " - data is " << data << std::endl;
	if (data == 7890) std::cout << " -- success." << std::endl;
	else std::cout << " -- not raedy. but may written after 3 sec." << std::endl;


   return RTC::RTC_OK;
}


/*
RTC::ReturnCode_t MyCons::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t MyCons::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t MyCons::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t MyCons::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t MyCons::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void MyConsInit(RTC::Manager* manager)
  {
    coil::Properties profile(mycons_spec);
    manager->registerFactory(profile,
                             RTC::Create<MyCons>,
                             RTC::Delete<MyCons>);
  }
  
};


