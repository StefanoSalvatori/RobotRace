#ifndef SIMPLE_CONTROLLER_H
#define SIMPLE_CONTROLLER_H

/*
 * Include some necessary headers.
 */
/* Definition of the CCI_Controller class. */
#include <argos3/core/control_interface/ci_controller.h>
/* Definition of the differential steering actuator */
#include <argos3/plugins/robots/generic/control_interface/ci_differential_steering_actuator.h>
/* Definition of the foot-bot proximity sensor */
#include <argos3/plugins/robots/foot-bot/control_interface/ci_footbot_proximity_sensor.h>

#include <argos3/plugins/robots/generic/control_interface/ci_leds_actuator.h>

#include <controllers/nn/perceptron.h>

/*
 * All the ARGoS stuff in the 'argos' namespace.
 * With this statement, you save typing argos:: every time.
 */
using namespace argos;

class SimpleController : public CCI_Controller
{
private:
   /* Pointer to the differential steering actuator */
   CCI_DifferentialSteeringActuator *wheels;

   /* Pointer to the foot-bot proximity sensor */
   CCI_FootBotProximitySensor *proximity;

   /* Pointer to the foot-bot proximity sensor */
   CCI_LEDsActuator *leds;

   /*
    * The following variables are used as parameters for the
    * algorithm. You can set their value in the <parameters> section
    * of the XML configuration file, under the
    * <controllers><footbot_diffusion_controller> section.
    */

   /* Wheel speeds */
   Real leftSpeed, rightSpeed = 0.0;

   /* The perceptron neural network */
   CPerceptron perceptron;

public:
   static const Real MAX_VELOCITY;
   static const int GENOME_SIZE;

   /* Class constructor. */
   SimpleController();

   /* Class destructor. */
   virtual ~SimpleController();

   /*
    * This function initializes the controller.
    * The 't_node' variable points to the <parameters> section in the XML
    */
   virtual void Init(TConfigurationNode &t_node);

   /*
    * This function is called once every time step.
    * The length of the time step is set in the XML file.
    */
   virtual void ControlStep();

   /*
    * This function resets the controller to its state right after the
    * Init().
    * It is called when you press the reset button in the GUI.
    */
   virtual void Reset();

   /*
    * Called to cleanup what done by Init() when the experiment finishes.
    */
   virtual void Destroy();

   inline CPerceptron &GetPerceptron()
   {
      return perceptron;
   }

   inline const CCI_FootBotProximitySensor::TReadings &GetProximityReadings()
   {
      return proximity->GetReadings();
   }

   inline const Real GetLeftSpeed()
   {
      return this->leftSpeed;
   }

   inline const Real GetRightSpeed()
   {
      return this->rightSpeed;
   }
};

#endif