#include <iostream>
#include "../BlastCompany/game.h"
#include <boost/config.hpp>
#include "../BlastCompany/systempipeline.h"
#include "../BlastCompany/functionmanager.h"
#include "../AnimationComponent/callbackactioncomponent.h"
#include <string>
#include <boost/any.hpp>
#include "../BlastCompany/context.h"
#include <inputevent.h>
#include <inputaction.h>
#include "../Box2DComponent/dynamicbodycomponent.h"
namespace game {

    class MainGame : public Game{
    private:
        nlohmann::json ball;
        Context *context;
        int c;
    public:
        void ballCallback(const boost::any &data, Component::CID animationCid){
            std::cout<<data.type().hash_code()<<std::endl;
            CallbackActionComponent::CallbackEventArgs args(boost::any_cast<const CallbackActionComponent::CallbackEventArgs&>(data));
            if(args.state == CallbackActionComponent::CallbackState::START)
                c++;
            if(c > 1000){
                this->context->getEcm().createEntityFromFile(ball);
                c=0;
            }
        }
        void leftAxis(const boost::any &data, Component::CID inputComponent){
            InputEvent event(boost::any_cast<const InputEvent&>(data));
            std::cout<<"action: " << event.getAction() << " axisVal: " << event.getAxisValue() << " buttonVal: " << event.getButtonValue()<<std::endl;
            std::cout<<"SIZ:" << event.getPackagedComponents().size()<<std::endl;
            DynamicBodyComponent* dynBod = dynamic_cast<DynamicBodyComponent*>(event.getPackagedComponents().at(0));
            b2Body *body = dynBod->getBody();
            if(event.getAction() == InputAction::STICK_L_X)
                body->ApplyForceToCenter(b2Vec2(event.getAxisValue()/10000.0,0), true);
            else if(event.getAction() == InputAction::STICK_L_Y)
                body->ApplyForceToCenter(b2Vec2(0,-event.getAxisValue()/10000.0), true);

        }
        void start(Context& context) override{
            std::cout<<"START"<<std::endl;
            this->context = &context;
            c = 0;
            context.getFuncMan().registerFunction("ballCallback", std::bind(&MainGame::ballCallback, this, std::placeholders::_1, std::placeholders::_2));
            context.getFuncMan().registerFunction("leftAxis", std::bind(&MainGame::leftAxis, this, std::placeholders::_1, std::placeholders::_2));

            //CallbackActionComponent::registerCallback("ballCallback",  game::ballCallback);
            std::ifstream baseballFile("./game/entities/baseball.json");

            baseballFile >> ball;
            baseballFile.close();
            std::cout<<"CREATING BALL"<<std::endl;
            this->context->getEcm().createEntityFromFile(ball);

            std::cout<<"LOADING GROUND !!!!!!!!!!!!"<<std::endl;

            std::ifstream groundFile("./game/entities/testentity.json");
            nlohmann::json j;
            groundFile >> j;
            groundFile.close();
            this->context->getEcm().createEntityFromFile(j);
        }
        void update() override{
            //std::cout<<"UPDATE"<<std::endl;
        }
        void end() override{
            std::cout<<"END"<<std::endl;
        }
    };
extern "C" BOOST_SYMBOL_EXPORT MainGame game;
MainGame game;
};
