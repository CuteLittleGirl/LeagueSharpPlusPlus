#include "PluginSDK.h"



ITexture* Hand;
ITexture* Sword;
IUnit* vayne;


void MakeTextures()
{
	Hand = GRender->CreateTextureFromFile("Hand1.png");
	Sword = GRender->CreateTextureFromFile("HoverEnemy.png");

}

PLUGIN_EVENT(void) OnRender(){

	Vec3 cursor;
	GGame->Projection(GGame->CursorPosition(), &cursor);
	Vec3 enemyToMouse;
	if (GOrbwalking->GetOrbwalkingMode() == kModeNone){
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 1500);
		if (target != nullptr){
			auto cursorOverChampion = (GGame->CursorPosition() - target->GetPosition()).Length2D();

			if (cursorOverChampion < 150){
				Sword->Draw(cursor.x, cursor.y);
				return;
			}
		}
		else {
			Hand->Draw(cursor.x, cursor.y);
		}
		
	}

	if (GOrbwalking->GetOrbwalkingMode() == kModeCombo){
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 550);
		if (target != nullptr && GOrbwalking->CanAttack()){
			GGame->Projection(target->GetPosition(), &enemyToMouse);
			Sword->Draw(enemyToMouse.x, enemyToMouse.y);
		}
		else{
			Hand->Draw(cursor.x, cursor.y);
		}
	}

}


PLUGIN_API void OnLoad(IPluginSDK* PluginSDK){
	PluginSDKSetup(PluginSDK);
	vayne = GEntityList->Player();
	GEventManager->AddEventHandler(kEventOnRender, OnRender);
	MakeTextures();

}

PLUGIN_API void OnUnload(){
	GEventManager->RemoveEventHandler(kEventOnRender, OnRender);
}