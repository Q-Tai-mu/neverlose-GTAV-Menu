/*
	THIS FILE IS A PART OF GTA V SCRIPT HOOK SDK
				http://dev-c.com
			(C) Alexander Blade 2015
*/

/*
	F4					activate
	NUM2/8/4/6			navigate thru the menus and lists (numlock must be on)
	NUM5 				select
	NUM0/BACKSPACE/F4 	back
	NUM9/3 				use vehicle boost when active
	NUM+ 				use vehicle rockets when active
*/

#include "script.h"
#include "keyboard.h"
#include <string>
#include <ctime>

#include <iostream>

#pragma warning(disable : 4244 4305) // double <-> float conversions
bool about = false;//约束提示框背景色是否渲染
bool Bottom = false;//最底框色
bool transparent = false;//透明的
void draw_rect(float A_0, float A_1, float A_2, float A_3, int A_4, int A_5, int A_6, int A_7)
{
	GRAPHICS::DRAW_RECT((A_0 + (A_2 * 0.5f)), (A_1 + (A_3 * 0.5f)), A_2, A_3, A_4, A_5, A_6, A_7);
}
void PlayFrontend(const std::string& sound_dict, const std::string& sound_name)
{
	AUDIO::PLAY_SOUND_FRONTEND(-1, const_cast<PCHAR>(sound_name.c_str()), const_cast<PCHAR>(sound_dict.c_str()), FALSE);
}

//					std:：字符串标题，				行宽度，				行高，			行顶，			行左，		文本左，			活动，		标题，		重缩放文本=true
void draw_menu_line(std::string caption, float lineWidth, float lineHeight, float lineTop, float lineLeft, float textLeft, bool active, bool title, bool rescaleText = true)
{
	// default values
	int text_col[4] = { 255, 255, 255, 200 }, //字体颜色
		rect_col[4] = { 1, 2, 3, 150 }; //选择框颜色
	float text_scale = 0.35;
	int font = 0;

	// correcting values for active line
	if (active)
	{
		//选中状态标字体题色
		text_col[0] = 255;
		text_col[1] = 255;
		text_col[2] = 255;

		//选中状态框色
		rect_col[0] = 138;//115//199
		rect_col[1] = 3;//100//200
		rect_col[2] = 3;//119//0

		if (rescaleText) text_scale = 0.40;
	}
	//提示约束框颜色
	if (about) {
		rect_col[0] = 36;
		rect_col[1] = 40;
		rect_col[2] = 47;
		//约束框字体颜色
		text_col[0] = 223;
		text_col[1] = 222;
		text_col[2] = 230;
		//透明的
		rect_col[3] = 255;
	}
	//底部文本框颜色
	if (Bottom) {
		rect_col[0] = 138;//128
		rect_col[1] = 3;//149
		rect_col[2] = 3;//154

		//标题字体颜色
		text_col[0] = 255;
		text_col[1] = 255;
		text_col[2] = 255;
		//透明的
		rect_col[3] = 255;
	}
	if (title)
	{
		//标题头颜色
		rect_col[0] = 138;//139//191//201
		rect_col[1] = 3;//145//83//222
		rect_col[2] = 3;//171//132//241
		//标题字体颜色
		text_col[0] = 255;
		text_col[1] = 255;
		text_col[2] = 255;
		//透明的
		rect_col[3] = 255;
		if (rescaleText) text_scale = 0.6;
		font = 1;
	}

	int screen_w, screen_h;
	GRAPHICS::GET_SCREEN_RESOLUTION(&screen_w, &screen_h);//获取屏幕分辨率

	textLeft += lineLeft;
	float lineWidthScaled = lineWidth / (float)screen_w + 0.025; // 看起来是菜单的整体宽度
	float lineTopScaled = lineTop / (float)screen_h + 0.025; //行顶部偏移
	float textLeftScaled = textLeft / (float)screen_w + (0.005); //字体 偏移
	float lineHeightScaled = lineHeight / (float)screen_h; //文本框的高度

	float lineLeftScaled = lineLeft / (float)screen_w; //看起来是透明度

	// 这是在原始脚本中是这样做的
	/*
	UI：：设置“文本”字体（字体）；
	UI：：设置_TEXT_比例（0.0，TEXT_比例）；
	UI：：设置_TEXT_颜色（TEXT_col[0]，TEXT_col[1]，TEXT_col[2]，TEXT_col[3]）；
	UI：：设置文本中心（0）；
	UI：：设置“文本”下拉列表（0，0，0，0，0）；
	UI：：设置文本边缘（0，0，0，0，0）；
	UI:：_SET_TEXT_ENTRY（“STRING”）；
	*/
	// 文本上半部分
	UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_SCALE(0.0, text_scale);
	UI::SET_TEXT_COLOUR(text_col[0], text_col[1], text_col[2], text_col[3]);
	UI::SET_TEXT_CENTRE(0);
	UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
	UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
	UI::_SET_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING((LPSTR)caption.c_str());
	UI::_DRAW_TEXT(textLeftScaled, (((lineTopScaled + 0.00278f) + lineHeightScaled) - 0.005f));
	
	// 文本下半部分
	UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_SCALE(0.0, text_scale);
	UI::SET_TEXT_COLOUR(text_col[0], text_col[1], text_col[2], text_col[3]);
	UI::SET_TEXT_CENTRE(0);
	UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
	UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
	UI::_SET_TEXT_GXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING((LPSTR)caption.c_str());
	int num25 = UI::_0x9040DFB09BE75706(textLeftScaled, (((lineTopScaled + 0.00278f) + lineHeightScaled) - 0.005f));

	// 绘制矩形
	draw_rect(lineLeftScaled, lineTopScaled + (0.00278f),
		lineWidthScaled, ((((float)(num25)*UI::_0xDB88A37483346780(text_scale, 0)) + (lineHeightScaled * 2.0f)) + 0.005f),
		rect_col[0], rect_col[1], rect_col[2], rect_col[3]);
}




bool trainer_switch_pressed()
{

	return IsKeyJustUp(VK_F4);
}

void get_button_state(bool* a, bool* b, bool* up, bool* down, bool* l, bool* r)
{
	if (a) *a = IsKeyDown(VK_RETURN);
	if (b) *b = IsKeyDown(VK_NUMPAD0) || trainer_switch_pressed() || IsKeyDown(VK_BACK);
	if (up) *up = IsKeyDown(VK_UP);
	if (down) *down = IsKeyDown(VK_DOWN);
	if (r) *r = IsKeyDown(VK_RIGHT);
	if (l) *l = IsKeyDown(VK_LEFT);
}

void menu_beep()
{
	AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
}

std::string statusText;
DWORD statusTextDrawTicksMax;
bool statusTextGxtEntry;

void update_status_text()
{
	if (GetTickCount() < statusTextDrawTicksMax)
	{

		UI::SET_TEXT_FONT(0);
		UI::SET_TEXT_SCALE(0.55, 0.55);
		UI::SET_TEXT_COLOUR(255, 255, 255, 255);
		UI::SET_TEXT_WRAP(0.0, 1.0);
		UI::SET_TEXT_CENTRE(1);
		UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
		UI::SET_TEXT_EDGE(1, 0, 0, 0, 205);
		if (statusTextGxtEntry)
		{
			UI::_SET_TEXT_ENTRY((char*)statusText.c_str());
		}
		else
		{
			UI::_SET_TEXT_ENTRY("STRING");
			UI::_ADD_TEXT_COMPONENT_STRING((char*)statusText.c_str());
		}
		UI::_DRAW_TEXT(0.5, 0.5);
	}
}

void set_status_text(std::string str, DWORD time = 2500, bool isGxtEntry = false)
{
	statusText = str;
	statusTextDrawTicksMax = GetTickCount() + time;
	statusTextGxtEntry = isGxtEntry;
}

// features
/*
特色播放器
功能播放器更新
特辑PlayerNeverwanted功能
功能播放忽略
功能PlayerIgnored已更新
功能播放限制
功能播放噪音
功能播放器更新
特色玩家快速游泳
功能播放机最新版本
featurePlayerFastRun功能
功能播放器未更新
功能播放器超级跳跃
特色武器诺雷洛德
特色武器火力弹药
特色武器爆炸性武器
爆炸武器
特色武器
*/
bool featurePlayerInvincible = false;
bool featurePlayerInvincibleUpdated = false;
bool featurePlayerNeverWanted = false;
bool featurePlayerIgnored = false;
bool featurePlayerIgnoredUpdated = false;
bool featurePlayerUnlimitedAbility = false;
bool featurePlayerNoNoise = false;
bool featurePlayerNoNoiseUpdated = false;
bool featurePlayerFastSwim = false;
bool featurePlayerFastSwimUpdated = false;
bool featurePlayerFastRun = false;
bool featurePlayerFastRunUpdated = false;
bool featurePlayerSuperJump = false;

bool featureWeaponNoReload = false;
bool featureWeaponFireAmmo = false;
bool featureWeaponExplosiveAmmo = false;
bool featureWeaponExplosiveMelee = false;
bool featureWeaponVehRockets = false;

DWORD featureWeaponVehShootLastTime = 0;

bool featureVehInvincible = false;
bool featureVehInvincibleUpdated = false;
bool featureVehInvincibleWheels = false;
bool featureVehInvincibleWheelsUpdated = false;
bool featureVehSeatbelt = false;
bool featureVehSeatbeltUpdated = false;
bool featureVehSpeedBoost = false;
bool featureVehWrapInSpawned = false;
bool featureVehmotorcycle = false;
bool featureVenaircraft = false;

bool featureWorldMoonGravity = false;
bool featureWorldRandomCops = true;
bool featureWorldRandomTrains = true;
bool featureWorldRandomBoats = true;
bool featureWorldGarbageTrucks = true;

bool featureTimePaused = false;
bool featureTimePausedUpdated = false;
bool featureTimeSynced = false;

bool featureWeatherWind = false;
bool featureWeatherPers = false;

bool featureMiscLockRadio = false;
bool featureMiscHideHud = false;


//玩家模式控制，需要时打开普通ped模式
void check_player_model()
{
	// 公共变量
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if (!ENTITY::DOES_ENTITY_EXIST(playerPed)) return;

	Hash model = ENTITY::GET_ENTITY_MODEL(playerPed);
	if (ENTITY::IS_ENTITY_DEAD(playerPed) || PLAYER::IS_PLAYER_BEING_ARRESTED(player, TRUE))
		if (model != GAMEPLAY::GET_HASH_KEY("player_zero") &&
			model != GAMEPLAY::GET_HASH_KEY("player_one") &&
			model != GAMEPLAY::GET_HASH_KEY("player_two"))
		{
			set_status_text("turning to normal");
			WAIT(1000);

			model = GAMEPLAY::GET_HASH_KEY("player_zero");
			STREAMING::REQUEST_MODEL(model);
			while (!STREAMING::HAS_MODEL_LOADED(model))
				WAIT(0);
			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), model);
			PED::SET_PED_DEFAULT_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID());
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);

			// 等到播放器被加压（注入？）
			while (ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID()) || PLAYER::IS_PLAYER_BEING_ARRESTED(player, TRUE))
				WAIT(0);

		}
}

void update_vehicle_guns()
{
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if (!ENTITY::DOES_ENTITY_EXIST(playerPed) || !featureWeaponVehRockets) return;

	bool bSelect = IsKeyDown(0x6B); // 更多
	if (bSelect && featureWeaponVehShootLastTime + 150 < GetTickCount() &&
		PLAYER::IS_PLAYER_CONTROL_ON(player) && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

		Vector3 v0, v1;
		GAMEPLAY::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(veh), &v0, &v1);

		Hash weaponAssetRocket = GAMEPLAY::GET_HASH_KEY("WEAPON_VEHICLE_ROCKET");
		if (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
		{
			WEAPON::REQUEST_WEAPON_ASSET(weaponAssetRocket, 31, 0);
			while (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
				WAIT(0);
		}

		Vector3 coords0from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -(v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords1from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, (v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords0to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -v1.x, v1.y + 100.0f, 0.1f);
		Vector3 coords1to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, v1.x, v1.y + 100.0f, 0.1f);

		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords0from.x, coords0from.y, coords0from.z,
			coords0to.x, coords0to.y, coords0to.z,
			250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);
		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1from.x, coords1from.y, coords1from.z,
			coords1to.x, coords1to.y, coords1to.z,
			250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);

		featureWeaponVehShootLastTime = GetTickCount();
	}
}

bool skinchanger_used = false;

// 更新游戏可以关闭的所有功能，称为每个游戏帧
void update_features()
{
	update_status_text();

	update_vehicle_guns();

	// 如果在另一个皮肤中死亡/被捕，请更改播放器型号，因为这会导致inf加载循环
	if (skinchanger_used)
		check_player_model();

	// 等到玩家准备好了，基本上防止玩家死亡或被捕时使用训练师
	while (ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID()) || PLAYER::IS_PLAYER_BEING_ARRESTED(PLAYER::PLAYER_ID(), TRUE))
		WAIT(0);

	// 从游戏中读取默认功能值
	featureWorldRandomCops = PED::CAN_CREATE_RANDOM_COPS() == TRUE;

	// 公共变量
	Player player = PLAYER::PLAYER_ID();

	Ped playerPed = PLAYER::PLAYER_PED_ID();
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(playerPed);

	// 玩家无敌
	if (featurePlayerInvincibleUpdated)
	{
		if (bPlayerExists && !featurePlayerInvincible)
			PLAYER::SET_PLAYER_INVINCIBLE(player, FALSE);
		featurePlayerInvincibleUpdated = false;
	}
	if (featurePlayerInvincible)
	{
		if (bPlayerExists)
			PLAYER::SET_PLAYER_INVINCIBLE(player, TRUE);
	}

	// 玩家消除警星
	if (featurePlayerNeverWanted)
	{
		if (bPlayerExists)
			PLAYER::CLEAR_PLAYER_WANTED_LEVEL(player);
	}

	// 警察忽视了玩家
	if (featurePlayerIgnoredUpdated)
	{
		if (bPlayerExists)
			PLAYER::SET_POLICE_IGNORE_PLAYER(player, featurePlayerIgnored);
		featurePlayerIgnoredUpdated = false;
	}

	// 玩家特殊能力
	if (featurePlayerUnlimitedAbility)
	{
		if (bPlayerExists)
			PLAYER::SPECIAL_ABILITY_FILL_METER(player, 1);
	}

	// 播放器无噪音
	if (featurePlayerNoNoiseUpdated)
	{
		if (bPlayerExists && !featurePlayerNoNoise)
			PLAYER::SET_PLAYER_NOISE_MULTIPLIER(player, 1.0);
		featurePlayerNoNoiseUpdated = false;
	}
	if (featurePlayerNoNoise)
		PLAYER::SET_PLAYER_NOISE_MULTIPLIER(player, 0.0);

	//快速游泳运动
	if (featurePlayerFastSwimUpdated)
	{
		if (bPlayerExists && !featurePlayerFastSwim)
			PLAYER::SET_SWIM_MULTIPLIER_FOR_PLAYER(player, 1.0);
		featurePlayerFastSwimUpdated = false;
	}
	if (featurePlayerFastSwim)
		PLAYER::SET_SWIM_MULTIPLIER_FOR_PLAYER(player, 1.49);

	// 玩家快跑
	if (featurePlayerFastRunUpdated)
	{
		if (bPlayerExists && !featurePlayerFastRun)
			PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(player, 1.0);
		featurePlayerFastRunUpdated = false;
	}
	if (featurePlayerFastRun)
		PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(player, 1.49);

	// 玩家超跳
	if (featurePlayerSuperJump)
	{
		if (bPlayerExists)
			GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(player);
	}

	// 武器
	if (featureWeaponFireAmmo)
	{
		if (bPlayerExists)
			GAMEPLAY::SET_FIRE_AMMO_THIS_FRAME(player);
	}
	if (featureWeaponExplosiveAmmo)
	{
		if (bPlayerExists)
			GAMEPLAY::SET_EXPLOSIVE_AMMO_THIS_FRAME(player);
	}
	if (featureWeaponExplosiveMelee)
	{
		if (bPlayerExists)
			GAMEPLAY::SET_EXPLOSIVE_MELEE_THIS_FRAME(player);
	}

	// 武器不需要重新装弹
	if (bPlayerExists && featureWeaponNoReload)
	{
		Hash cur;
		if (WEAPON::GET_CURRENT_PED_WEAPON(playerPed, &cur, 1))
		{
			if (WEAPON::IS_WEAPON_VALID(cur))
			{
				int maxAmmo;
				if (WEAPON::GET_MAX_AMMO(playerPed, cur, &maxAmmo))
				{
					WEAPON::SET_PED_AMMO(playerPed, cur, maxAmmo);

					maxAmmo = WEAPON::GET_MAX_AMMO_IN_CLIP(playerPed, cur, 1);
					if (maxAmmo > 0)
						WEAPON::SET_AMMO_IN_CLIP(playerPed, cur, maxAmmo);
				}
			}
		}
	}

	// 玩家战车无敌
	if (featureVehInvincibleUpdated)
	{
		if (bPlayerExists && !featureVehInvincible && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			ENTITY::SET_ENTITY_INVINCIBLE(veh, FALSE);
			ENTITY::SET_ENTITY_PROOFS(veh, 0, 0, 0, 0, 0, 0, 0, 0);
			VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, 1);
			VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(veh, 1);
			VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(veh, 1);
		}
		featureVehInvincibleUpdated = false;
	}
	if (featureVehInvincible)
	{
		if (bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			ENTITY::SET_ENTITY_INVINCIBLE(veh, TRUE);
			ENTITY::SET_ENTITY_PROOFS(veh, 1, 1, 1, 1, 1, 1, 1, 1);
			VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, 0);
			VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(veh, 0);
			VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(veh, 0);
		}
	}

	// 玩家的车辆车轮，可用于定制操作
	if (featureVehInvincibleWheelsUpdated)
	{
		if (bPlayerExists && !featureVehInvincibleWheels && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, TRUE);
			VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(veh, TRUE);
			VEHICLE::SET_VEHICLE_HAS_STRONG_AXLES(veh, FALSE);
		}
		featureVehInvincibleWheelsUpdated = false;
	}
	if (featureVehInvincibleWheels)
	{
		if (bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, FALSE);
			VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(veh, FALSE);
			VEHICLE::SET_VEHICLE_HAS_STRONG_AXLES(veh, TRUE);
		}
	}

	// 安全带
	const int PED_FLAG_CAN_FLY_THRU_WINDSCREEN = 32;
	if (featureVehSeatbeltUpdated)
	{
		if (bPlayerExists && !featureVehSeatbelt)
			PED::SET_PED_CONFIG_FLAG(playerPed, PED_FLAG_CAN_FLY_THRU_WINDSCREEN, TRUE);
		featureVehSeatbeltUpdated = false;
	}
	if (featureVehSeatbelt)
	{
		if (bPlayerExists)
		{
			if (PED::GET_PED_CONFIG_FLAG(playerPed, PED_FLAG_CAN_FLY_THRU_WINDSCREEN, TRUE))
				PED::SET_PED_CONFIG_FLAG(playerPed, PED_FLAG_CAN_FLY_THRU_WINDSCREEN, FALSE);
		}
	}

	// 玩家车辆提升
	if (featureVehSpeedBoost && bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
		DWORD model = ENTITY::GET_ENTITY_MODEL(veh);

		bool bUp = IsKeyDown(VK_NUMPAD9);
		bool bDown = IsKeyDown(VK_NUMPAD3);

		if (bUp || bDown)
		{
			float speed = ENTITY::GET_ENTITY_SPEED(veh);
			if (bUp)
			{
				if (speed < 3.0f) speed = 3.0f;
				speed += speed * 0.05f;
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, speed);
			}
			else
				if (ENTITY::IS_ENTITY_IN_AIR(veh) || speed > 5.0)
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, 0.0);
		}
	}

	// 时间暂停
	if (featureTimePausedUpdated)
	{
		TIME::PAUSE_CLOCK(featureTimePaused);
		featureTimePausedUpdated = false;
	}

	// 时间同步
	if (featureTimeSynced)
	{
		time_t now = time(0);
		tm t;
		localtime_s(&t, &now);
		TIME::SET_CLOCK_TIME(t.tm_hour, t.tm_min, t.tm_sec);
	}

	// hide hud
	if (featureMiscHideHud)
		UI::HIDE_HUD_AND_RADAR_THIS_FRAME();
}

LPCSTR pedModels[70][10] = {
	{"player_zero", "player_one", "player_two", "a_c_boar", "a_c_chimp", "a_c_cow", "a_c_coyote", "a_c_deer", "a_c_fish", "a_c_hen"},
	{ "a_c_cat_01", "a_c_chickenhawk", "a_c_cormorant", "a_c_crow", "a_c_dolphin", "a_c_humpback", "a_c_killerwhale", "a_c_pigeon", "a_c_seagull", "a_c_sharkhammer"},
	{"a_c_pig", "a_c_rat", "a_c_rhesus", "a_c_chop", "a_c_husky", "a_c_mtlion", "a_c_retriever", "a_c_sharktiger", "a_c_shepherd", "s_m_m_movalien_01"},
	{"a_f_m_beach_01", "a_f_m_bevhills_01", "a_f_m_bevhills_02", "a_f_m_bodybuild_01", "a_f_m_business_02", "a_f_m_downtown_01", "a_f_m_eastsa_01", "a_f_m_eastsa_02", "a_f_m_fatbla_01", "a_f_m_fatcult_01"},
	{"a_f_m_fatwhite_01", "a_f_m_ktown_01", "a_f_m_ktown_02", "a_f_m_prolhost_01", "a_f_m_salton_01", "a_f_m_skidrow_01", "a_f_m_soucentmc_01", "a_f_m_soucent_01", "a_f_m_soucent_02", "a_f_m_tourist_01"},
	{"a_f_m_trampbeac_01", "a_f_m_tramp_01", "a_f_o_genstreet_01", "a_f_o_indian_01", "a_f_o_ktown_01", "a_f_o_salton_01", "a_f_o_soucent_01", "a_f_o_soucent_02", "a_f_y_beach_01", "a_f_y_bevhills_01"},
	{"a_f_y_bevhills_02", "a_f_y_bevhills_03", "a_f_y_bevhills_04", "a_f_y_business_01", "a_f_y_business_02", "a_f_y_business_03", "a_f_y_business_04", "a_f_y_eastsa_01", "a_f_y_eastsa_02", "a_f_y_eastsa_03"},
	{"a_f_y_epsilon_01", "a_f_y_fitness_01", "a_f_y_fitness_02", "a_f_y_genhot_01", "a_f_y_golfer_01", "a_f_y_hiker_01", "a_f_y_hippie_01", "a_f_y_hipster_01", "a_f_y_hipster_02", "a_f_y_hipster_03"},
	{"a_f_y_hipster_04", "a_f_y_indian_01", "a_f_y_juggalo_01", "a_f_y_runner_01", "a_f_y_rurmeth_01", "a_f_y_scdressy_01", "a_f_y_skater_01", "a_f_y_soucent_01", "a_f_y_soucent_02", "a_f_y_soucent_03"},
	{"a_f_y_tennis_01", "a_f_y_topless_01", "a_f_y_tourist_01", "a_f_y_tourist_02", "a_f_y_vinewood_01", "a_f_y_vinewood_02", "a_f_y_vinewood_03", "a_f_y_vinewood_04", "a_f_y_yoga_01", "a_m_m_acult_01"},
	{"a_m_m_afriamer_01", "a_m_m_beach_01", "a_m_m_beach_02", "a_m_m_bevhills_01", "a_m_m_bevhills_02", "a_m_m_business_01", "a_m_m_eastsa_01", "a_m_m_eastsa_02", "a_m_m_farmer_01", "a_m_m_fatlatin_01"},
	{"a_m_m_genfat_01", "a_m_m_genfat_02", "a_m_m_golfer_01", "a_m_m_hasjew_01", "a_m_m_hillbilly_01", "a_m_m_hillbilly_02", "a_m_m_indian_01", "a_m_m_ktown_01", "a_m_m_malibu_01", "a_m_m_mexcntry_01"},
	{"a_m_m_mexlabor_01", "a_m_m_og_boss_01", "a_m_m_paparazzi_01", "a_m_m_polynesian_01", "a_m_m_prolhost_01", "a_m_m_rurmeth_01", "a_m_m_salton_01", "a_m_m_salton_02", "a_m_m_salton_03", "a_m_m_salton_04"},
	{"a_m_m_skater_01", "a_m_m_skidrow_01", "a_m_m_socenlat_01", "a_m_m_soucent_01", "a_m_m_soucent_02", "a_m_m_soucent_03", "a_m_m_soucent_04", "a_m_m_stlat_02", "a_m_m_tennis_01", "a_m_m_tourist_01"},
	{"a_m_m_trampbeac_01", "a_m_m_tramp_01", "a_m_m_tranvest_01", "a_m_m_tranvest_02", "a_m_o_acult_01", "a_m_o_acult_02", "a_m_o_beach_01", "a_m_o_genstreet_01", "a_m_o_ktown_01", "a_m_o_salton_01"},
	{"a_m_o_soucent_01", "a_m_o_soucent_02", "a_m_o_soucent_03", "a_m_o_tramp_01", "a_m_y_acult_01", "a_m_y_acult_02", "a_m_y_beachvesp_01", "a_m_y_beachvesp_02", "a_m_y_beach_01", "a_m_y_beach_02"},
	{"a_m_y_beach_03", "a_m_y_bevhills_01", "a_m_y_bevhills_02", "a_m_y_breakdance_01", "a_m_y_busicas_01", "a_m_y_business_01", "a_m_y_business_02", "a_m_y_business_03", "a_m_y_cyclist_01", "a_m_y_dhill_01"},
	{"a_m_y_downtown_01", "a_m_y_eastsa_01", "a_m_y_eastsa_02", "a_m_y_epsilon_01", "a_m_y_epsilon_02", "a_m_y_gay_01", "a_m_y_gay_02", "a_m_y_genstreet_01", "a_m_y_genstreet_02", "a_m_y_golfer_01"},
	{"a_m_y_hasjew_01", "a_m_y_hiker_01", "a_m_y_hippy_01", "a_m_y_hipster_01", "a_m_y_hipster_02", "a_m_y_hipster_03", "a_m_y_indian_01", "a_m_y_jetski_01", "a_m_y_juggalo_01", "a_m_y_ktown_01"},
	{"a_m_y_ktown_02", "a_m_y_latino_01", "a_m_y_methhead_01", "a_m_y_mexthug_01", "a_m_y_motox_01", "a_m_y_motox_02", "a_m_y_musclbeac_01", "a_m_y_musclbeac_02", "a_m_y_polynesian_01", "a_m_y_roadcyc_01"},
	{"a_m_y_runner_01", "a_m_y_runner_02", "a_m_y_salton_01", "a_m_y_skater_01", "a_m_y_skater_02", "a_m_y_soucent_01", "a_m_y_soucent_02", "a_m_y_soucent_03", "a_m_y_soucent_04", "a_m_y_stbla_01"},
	{"a_m_y_stbla_02", "a_m_y_stlat_01", "a_m_y_stwhi_01", "a_m_y_stwhi_02", "a_m_y_sunbathe_01", "a_m_y_surfer_01", "a_m_y_vindouche_01", "a_m_y_vinewood_01", "a_m_y_vinewood_02", "a_m_y_vinewood_03"},
	{"a_m_y_vinewood_04", "a_m_y_yoga_01", "u_m_y_proldriver_01", "u_m_y_rsranger_01", "u_m_y_sbike", "u_m_y_staggrm_01", "u_m_y_tattoo_01", "csb_abigail", "csb_anita", "csb_anton"},
	{"csb_ballasog", "csb_bride", "csb_burgerdrug", "csb_car3guy1", "csb_car3guy2", "csb_chef", "csb_chin_goon", "csb_cletus", "csb_cop", "csb_customer"},
	{"csb_denise_friend", "csb_fos_rep", "csb_g", "csb_groom", "csb_grove_str_dlr", "csb_hao", "csb_hugh", "csb_imran", "csb_janitor", "csb_maude"},
	{"csb_mweather", "csb_ortega", "csb_oscar", "csb_porndudes", "csb_porndudes_p", "csb_prologuedriver", "csb_prolsec", "csb_ramp_gang", "csb_ramp_hic", "csb_ramp_hipster"},
	{"csb_ramp_marine", "csb_ramp_mex", "csb_reporter", "csb_roccopelosi", "csb_screen_writer", "csb_stripper_01", "csb_stripper_02", "csb_tonya", "csb_trafficwarden", "cs_amandatownley"},
	{"cs_andreas", "cs_ashley", "cs_bankman", "cs_barry", "cs_barry_p", "cs_beverly", "cs_beverly_p", "cs_brad", "cs_bradcadaver", "cs_carbuyer"},
	{"cs_casey", "cs_chengsr", "cs_chrisformage", "cs_clay", "cs_dale", "cs_davenorton", "cs_debra", "cs_denise", "cs_devin", "cs_dom"},
	{"cs_dreyfuss", "cs_drfriedlander", "cs_fabien", "cs_fbisuit_01", "cs_floyd", "cs_guadalope", "cs_gurk", "cs_hunter", "cs_janet", "cs_jewelass"},
	{"cs_jimmyboston", "cs_jimmydisanto", "cs_joeminuteman", "cs_johnnyklebitz", "cs_josef", "cs_josh", "cs_lamardavis", "cs_lazlow", "cs_lestercrest", "cs_lifeinvad_01"},
	{"cs_magenta", "cs_manuel", "cs_marnie", "cs_martinmadrazo", "cs_maryann", "cs_michelle", "cs_milton", "cs_molly", "cs_movpremf_01", "cs_movpremmale"},
	{"cs_mrk", "cs_mrsphillips", "cs_mrs_thornhill", "cs_natalia", "cs_nervousron", "cs_nigel", "cs_old_man1a", "cs_old_man2", "cs_omega", "cs_orleans"},
	{"cs_paper", "cs_paper_p", "cs_patricia", "cs_priest", "cs_prolsec_02", "cs_russiandrunk", "cs_siemonyetarian", "cs_solomon", "cs_stevehains", "cs_stretch"},
	{"cs_tanisha", "cs_taocheng", "cs_taostranslator", "cs_tenniscoach", "cs_terry", "cs_tom", "cs_tomepsilon", "cs_tracydisanto", "cs_wade", "cs_zimbor"},
	{"g_f_y_ballas_01", "g_f_y_families_01", "g_f_y_lost_01", "g_f_y_vagos_01", "g_m_m_armboss_01", "g_m_m_armgoon_01", "g_m_m_armlieut_01", "g_m_m_chemwork_01", "g_m_m_chemwork_01_p", "g_m_m_chiboss_01"},
	{"g_m_m_chiboss_01_p", "g_m_m_chicold_01", "g_m_m_chicold_01_p", "g_m_m_chigoon_01", "g_m_m_chigoon_01_p", "g_m_m_chigoon_02", "g_m_m_korboss_01", "g_m_m_mexboss_01", "g_m_m_mexboss_02", "g_m_y_armgoon_02"},
	{"g_m_y_azteca_01", "g_m_y_ballaeast_01", "g_m_y_ballaorig_01", "g_m_y_ballasout_01", "g_m_y_famca_01", "g_m_y_famdnf_01", "g_m_y_famfor_01", "g_m_y_korean_01", "g_m_y_korean_02", "g_m_y_korlieut_01"},
	{"g_m_y_lost_01", "g_m_y_lost_02", "g_m_y_lost_03", "g_m_y_mexgang_01", "g_m_y_mexgoon_01", "g_m_y_mexgoon_02", "g_m_y_mexgoon_03", "g_m_y_mexgoon_03_p", "g_m_y_pologoon_01", "g_m_y_pologoon_01_p"},
	{"g_m_y_pologoon_02", "g_m_y_pologoon_02_p", "g_m_y_salvaboss_01", "g_m_y_salvagoon_01", "g_m_y_salvagoon_02", "g_m_y_salvagoon_03", "g_m_y_salvagoon_03_p", "g_m_y_strpunk_01", "g_m_y_strpunk_02", "hc_driver"},
	{"hc_gunman", "hc_hacker", "ig_abigail", "ig_amandatownley", "ig_andreas", "ig_ashley", "ig_ballasog", "ig_bankman", "ig_barry", "ig_barry_p"},
	{"ig_bestmen", "ig_beverly", "ig_beverly_p", "ig_brad", "ig_bride", "ig_car3guy1", "ig_car3guy2", "ig_casey", "ig_chef", "ig_chengsr"},
	{"ig_chrisformage", "ig_clay", "ig_claypain", "ig_cletus", "ig_dale", "ig_davenorton", "ig_denise", "ig_devin", "ig_dom", "ig_dreyfuss"},
	{"ig_drfriedlander", "ig_fabien", "ig_fbisuit_01", "ig_floyd", "ig_groom", "ig_hao", "ig_hunter", "ig_janet", "ig_jay_norris", "ig_jewelass"},
	{"ig_jimmyboston", "ig_jimmydisanto", "ig_joeminuteman", "ig_johnnyklebitz", "ig_josef", "ig_josh", "ig_kerrymcintosh", "ig_lamardavis", "ig_lazlow", "ig_lestercrest"},
	{"ig_lifeinvad_01", "ig_lifeinvad_02", "ig_magenta", "ig_manuel", "ig_marnie", "ig_maryann", "ig_maude", "ig_michelle", "ig_milton", "ig_molly"},
	{"ig_mrk", "ig_mrsphillips", "ig_mrs_thornhill", "ig_natalia", "ig_nervousron", "ig_nigel", "ig_old_man1a", "ig_old_man2", "ig_omega", "ig_oneil"},
	{"ig_orleans", "ig_ortega", "ig_paper", "ig_patricia", "ig_priest", "ig_prolsec_02", "ig_ramp_gang", "ig_ramp_hic", "ig_ramp_hipster", "ig_ramp_mex"},
	{"ig_roccopelosi", "ig_russiandrunk", "ig_screen_writer", "ig_siemonyetarian", "ig_solomon", "ig_stevehains", "ig_stretch", "ig_talina", "ig_tanisha", "ig_taocheng"},
	{"ig_taostranslator", "ig_taostranslator_p", "ig_tenniscoach", "ig_terry", "ig_tomepsilon", "ig_tonya", "ig_tracydisanto", "ig_trafficwarden", "ig_tylerdix", "ig_wade"},
	{"ig_zimbor", "mp_f_deadhooker", "mp_f_freemode_01", "mp_f_misty_01", "mp_f_stripperlite", "mp_g_m_pros_01", "mp_headtargets", "mp_m_claude_01", "mp_m_exarmy_01", "mp_m_famdd_01"},
	{"mp_m_fibsec_01", "mp_m_freemode_01", "mp_m_marston_01", "mp_m_niko_01", "mp_m_shopkeep_01", "mp_s_m_armoured_01", "", "", "", ""},
	{"", "s_f_m_fembarber", "s_f_m_maid_01", "s_f_m_shop_high", "s_f_m_sweatshop_01", "s_f_y_airhostess_01", "s_f_y_bartender_01", "s_f_y_baywatch_01", "s_f_y_cop_01", "s_f_y_factory_01"},
	{"s_f_y_hooker_01", "s_f_y_hooker_02", "s_f_y_hooker_03", "s_f_y_migrant_01", "s_f_y_movprem_01", "s_f_y_ranger_01", "s_f_y_scrubs_01", "s_f_y_sheriff_01", "s_f_y_shop_low", "s_f_y_shop_mid"},
	{"s_f_y_stripperlite", "s_f_y_stripper_01", "s_f_y_stripper_02", "s_f_y_sweatshop_01", "s_m_m_ammucountry", "s_m_m_armoured_01", "s_m_m_armoured_02", "s_m_m_autoshop_01", "s_m_m_autoshop_02", "s_m_m_bouncer_01"},
	{"s_m_m_chemsec_01", "s_m_m_ciasec_01", "s_m_m_cntrybar_01", "s_m_m_dockwork_01", "s_m_m_doctor_01", "s_m_m_fiboffice_01", "s_m_m_fiboffice_02", "s_m_m_gaffer_01", "s_m_m_gardener_01", "s_m_m_gentransport"},
	{"s_m_m_hairdress_01", "s_m_m_highsec_01", "s_m_m_highsec_02", "s_m_m_janitor", "s_m_m_lathandy_01", "s_m_m_lifeinvad_01", "s_m_m_linecook", "s_m_m_lsmetro_01", "s_m_m_mariachi_01", "s_m_m_marine_01"},
	{"s_m_m_marine_02", "s_m_m_migrant_01", "u_m_y_zombie_01", "s_m_m_movprem_01", "s_m_m_movspace_01", "s_m_m_paramedic_01", "s_m_m_pilot_01", "s_m_m_pilot_02", "s_m_m_postal_01", "s_m_m_postal_02"},
	{"s_m_m_prisguard_01", "s_m_m_scientist_01", "s_m_m_security_01", "s_m_m_snowcop_01", "s_m_m_strperf_01", "s_m_m_strpreach_01", "s_m_m_strvend_01", "s_m_m_trucker_01", "s_m_m_ups_01", "s_m_m_ups_02"},
	{"s_m_o_busker_01", "s_m_y_airworker", "s_m_y_ammucity_01", "s_m_y_armymech_01", "s_m_y_autopsy_01", "s_m_y_barman_01", "s_m_y_baywatch_01", "s_m_y_blackops_01", "s_m_y_blackops_02", "s_m_y_busboy_01"},
	{"s_m_y_chef_01", "s_m_y_clown_01", "s_m_y_construct_01", "s_m_y_construct_02", "s_m_y_cop_01", "s_m_y_dealer_01", "s_m_y_devinsec_01", "s_m_y_dockwork_01", "s_m_y_doorman_01", "s_m_y_dwservice_01"},
	{"s_m_y_dwservice_02", "s_m_y_factory_01", "s_m_y_fireman_01", "s_m_y_garbage", "s_m_y_grip_01", "s_m_y_hwaycop_01", "s_m_y_marine_01", "s_m_y_marine_02", "s_m_y_marine_03", "s_m_y_mime"},
	{"s_m_y_pestcont_01", "s_m_y_pilot_01", "s_m_y_prismuscl_01", "s_m_y_prisoner_01", "s_m_y_ranger_01", "s_m_y_robber_01", "s_m_y_sheriff_01", "s_m_y_shop_mask", "s_m_y_strvend_01", "s_m_y_swat_01"},
	{"s_m_y_uscg_01", "s_m_y_valet_01", "s_m_y_waiter_01", "s_m_y_winclean_01", "s_m_y_xmech_01", "s_m_y_xmech_02", "u_f_m_corpse_01", "u_f_m_miranda", "u_f_m_promourn_01", "u_f_o_moviestar"},
	{"u_f_o_prolhost_01", "u_f_y_bikerchic", "u_f_y_comjane", "u_f_y_corpse_01", "u_f_y_corpse_02", "u_f_y_hotposh_01", "u_f_y_jewelass_01", "u_f_y_mistress", "u_f_y_poppymich", "u_f_y_princess"},
	{"u_f_y_spyactress", "u_m_m_aldinapoli", "u_m_m_bankman", "u_m_m_bikehire_01", "u_m_m_fibarchitect", "u_m_m_filmdirector", "u_m_m_glenstank_01", "u_m_m_griff_01", "u_m_m_jesus_01", "u_m_m_jewelsec_01"},
	{"u_m_m_jewelthief", "u_m_m_markfost", "u_m_m_partytarget", "u_m_m_prolsec_01", "u_m_m_promourn_01", "u_m_m_rivalpap", "u_m_m_spyactor", "u_m_m_willyfist", "u_m_o_finguru_01", "u_m_o_taphillbilly"},
	{"u_m_o_tramp_01", "u_m_y_abner", "u_m_y_antonb", "u_m_y_babyd", "u_m_y_baygor", "u_m_y_burgerdrug_01", "u_m_y_chip", "u_m_y_cyclist_01", "u_m_y_fibmugger_01", "u_m_y_guido_01"},
	{"u_m_y_gunvend_01", "u_m_y_hippie_01", "u_m_y_imporage", "u_m_y_justin", "u_m_y_mani", "u_m_y_militarybum", "u_m_y_paparazzi", "u_m_y_party_01", "u_m_y_pogo_01", "u_m_y_prisoner_01"},
	{"ig_benny", "ig_g", "ig_vagspeak", "mp_m_g_vagfun_01", "mp_m_boatstaff_01", "mp_f_boatstaff_01", "", "", "", ""}
};

LPCSTR pedModelNames[70][10] = {
	{"MICHAEL", "FRANKLIN", "TREVOR", "BOAR", "CHIMP", "COW", "COYOTE", "DEER", "FISH", "HEN"},
	{ "CAT", "HAWK", "CORMORANT", "CROW", "DOLPHIN", "HUMPBACK", "WHALE", "PIGEON", "SEAGULL", "SHARKHAMMER" },
	{"PIG", "RAT", "RHESUS", "CHOP", "HUSKY", "MTLION", "RETRIEVER", "SHARKTIGER", "SHEPHERD", "ALIEN"},
	{"BEACH", "BEVHILLS", "BEVHILLS", "BODYBUILD", "BUSINESS", "DOWNTOWN", "EASTSA", "EASTSA", "FATBLA", "FATCULT"},
	{"FATWHITE", "KTOWN", "KTOWN", "PROLHOST", "SALTON", "SKIDROW", "SOUCENTMC", "SOUCENT", "SOUCENT", "TOURIST"},
	{"TRAMPBEAC", "TRAMP", "GENSTREET", "INDIAN", "KTOWN", "SALTON", "SOUCENT", "SOUCENT", "BEACH", "BEVHILLS"},
	{"BEVHILLS", "BEVHILLS", "BEVHILLS", "BUSINESS", "BUSINESS", "BUSINESS", "BUSINESS", "EASTSA", "EASTSA", "EASTSA"},
	{"EPSILON", "FITNESS", "FITNESS", "GENHOT", "GOLFER", "HIKER", "HIPPIE", "HIPSTER", "HIPSTER", "HIPSTER"},
	{"HIPSTER", "INDIAN", "JUGGALO", "RUNNER", "RURMETH", "SCDRESSY", "SKATER", "SOUCENT", "SOUCENT", "SOUCENT"},
	{"TENNIS", "TOPLESS", "TOURIST", "TOURIST", "VINEWOOD", "VINEWOOD", "VINEWOOD", "VINEWOOD", "YOGA", "ACULT"},
	{"AFRIAMER", "BEACH", "BEACH", "BEVHILLS", "BEVHILLS", "BUSINESS", "EASTSA", "EASTSA", "FARMER", "FATLATIN"},
	{"GENFAT", "GENFAT", "GOLFER", "HASJEW", "HILLBILLY", "HILLBILLY", "INDIAN", "KTOWN", "MALIBU", "MEXCNTRY"},
	{"MEXLABOR", "OG_BOSS", "PAPARAZZI", "POLYNESIAN", "PROLHOST", "RURMETH", "SALTON", "SALTON", "SALTON", "SALTON"},
	{"SKATER", "SKIDROW", "SOCENLAT", "SOUCENT", "SOUCENT", "SOUCENT", "SOUCENT", "STLAT", "TENNIS", "TOURIST"},
	{"TRAMPBEAC", "TRAMP", "TRANVEST", "TRANVEST", "ACULT", "ACULT", "BEACH", "GENSTREET", "KTOWN", "SALTON"},
	{"SOUCENT", "SOUCENT", "SOUCENT", "TRAMP", "ACULT", "ACULT", "BEACHVESP", "BEACHVESP", "BEACH", "BEACH"},
	{"BEACH", "BEVHILLS", "BEVHILLS", "BREAKDANCE", "BUSICAS", "BUSINESS", "BUSINESS", "BUSINESS", "CYCLIST", "DHILL"},
	{"DOWNTOWN", "EASTSA", "EASTSA", "EPSILON", "EPSILON", "GAY", "GAY", "GENSTREET", "GENSTREET", "GOLFER"},
	{"HASJEW", "HIKER", "HIPPY", "HIPSTER", "HIPSTER", "HIPSTER", "INDIAN", "JETSKI", "JUGGALO", "KTOWN"},
	{"KTOWN", "LATINO", "METHHEAD", "MEXTHUG", "MOTOX", "MOTOX", "MUSCLBEAC", "MUSCLBEAC", "POLYNESIAN", "ROADCYC"},
	{"RUNNER", "RUNNER", "SALTON", "SKATER", "SKATER", "SOUCENT", "SOUCENT", "SOUCENT", "SOUCENT", "STBLA"},
	{"STBLA", "STLAT", "STWHI", "STWHI", "SUNBATHE", "SURFER", "VINDOUCHE", "VINEWOOD", "VINEWOOD", "VINEWOOD"},
	{"VINEWOOD", "YOGA", "PROLDRIVER", "RSRANGER", "SBIKE", "STAGGRM", "TATTOO", "ABIGAIL", "ANITA", "ANTON"},
	{"BALLASOG", "BRIDE", "BURGERDRUG", "CAR3GUY1", "CAR3GUY2", "CHEF", "CHIN_GOON", "CLETUS", "COP", "CUSTOMER"},
	{"DENISE_FRIEND", "FOS_REP", "G", "GROOM", "DLR", "HAO", "HUGH", "IMRAN", "JANITOR", "MAUDE"},
	{"MWEATHER", "ORTEGA", "OSCAR", "PORNDUDES", "PORNDUDES_P", "PROLOGUEDRIVER", "PROLSEC", "GANG", "HIC", "HIPSTER"},
	{"MARINE", "MEX", "REPORTER", "ROCCOPELOSI", "SCREEN_WRITER", "STRIPPER", "STRIPPER", "TONYA", "TRAFFICWARDEN", "AMANDATOWNLEY"},
	{"ANDREAS", "ASHLEY", "BANKMAN", "BARRY", "BARRY_P", "BEVERLY", "BEVERLY_P", "BRAD", "BRADCADAVER", "CARBUYER"},
	{"CASEY", "CHENGSR", "CHRISFORMAGE", "CLAY", "DALE", "DAVENORTON", "DEBRA", "DENISE", "DEVIN", "DOM"},
	{"DREYFUSS", "DRFRIEDLANDER", "FABIEN", "FBISUIT", "FLOYD", "GUADALOPE", "GURK", "HUNTER", "JANET", "JEWELASS"},
	{"JIMMYBOSTON", "JIMMYDISANTO", "JOEMINUTEMAN", "JOHNNYKLEBITZ", "JOSEF", "JOSH", "LAMARDAVIS", "LAZLOW", "LESTERCREST", "LIFEINVAD"},
	{"MAGENTA", "MANUEL", "MARNIE", "MARTINMADRAZO", "MARYANN", "MICHELLE", "MILTON", "MOLLY", "MOVPREMF", "MOVPREMMALE"},
	{"MRK", "MRSPHILLIPS", "MRS_THORNHILL", "NATALIA", "NERVOUSRON", "NIGEL", "OLD_MAN1A", "OLD_MAN2", "OMEGA", "ORLEANS"},
	{"PAPER", "PAPER_P", "PATRICIA", "PRIEST", "PROLSEC", "RUSSIANDRUNK", "SIEMONYETARIAN", "SOLOMON", "STEVEHAINS", "STRETCH"},
	{"TANISHA", "TAOCHENG", "TAOSTRANSLATOR", "TENNISCOACH", "TERRY", "TOM", "TOMEPSILON", "TRACYDISANTO", "WADE", "ZIMBOR"},
	{"BALLAS", "FAMILIES", "LOST", "VAGOS", "ARMBOSS", "ARMGOON", "ARMLIEUT", "CHEMWORK", "CHEMWORK_P", "CHIBOSS"},
	{"CHIBOSS_P", "CHICOLD", "CHICOLD_P", "CHIGOON", "CHIGOON_P", "CHIGOON", "KORBOSS", "MEXBOSS", "MEXBOSS", "ARMGOON"},
	{"AZTECA", "BALLAEAST", "BALLAORIG", "BALLASOUT", "FAMCA", "FAMDNF", "FAMFOR", "KOREAN", "KOREAN", "KORLIEUT"},
	{"LOST", "LOST", "LOST", "MEXGANG", "MEXGOON", "MEXGOON", "MEXGOON", "MEXGOON_P", "POLOGOON", "POLOGOON_P"},
	{"POLOGOON", "POLOGOON_P", "SALVABOSS", "SALVAGOON", "SALVAGOON", "SALVAGOON", "SALVAGOON_P", "STRPUNK", "STRPUNK", "HC_DRIVER"},
	{"HC_GUNMAN", "HC_HACKER", "ABIGAIL", "AMANDATOWNLEY", "ANDREAS", "ASHLEY", "BALLASOG", "BANKMAN", "BARRY", "BARRY_P"},
	{"BESTMEN", "BEVERLY", "BEVERLY_P", "BRAD", "BRIDE", "CAR3GUY1", "CAR3GUY2", "CASEY", "CHEF", "CHENGSR"},
	{"CHRISFORMAGE", "CLAY", "CLAYPAIN", "CLETUS", "DALE", "DAVENORTON", "DENISE", "DEVIN", "DOM", "DREYFUSS"},
	{"DRFRIEDLANDER", "FABIEN", "FBISUIT", "FLOYD", "GROOM", "HAO", "HUNTER", "JANET", "JAY_NORRIS", "JEWELASS"},
	{"JIMMYBOSTON", "JIMMYDISANTO", "JOEMINUTEMAN", "JOHNNYKLEBITZ", "JOSEF", "JOSH", "KERRYMCINTOSH", "LAMARDAVIS", "LAZLOW", "LESTERCREST"},
	{"LIFEINVAD", "LIFEINVAD", "MAGENTA", "MANUEL", "MARNIE", "MARYANN", "MAUDE", "MICHELLE", "MILTON", "MOLLY"},
	{"MRK", "MRSPHILLIPS", "MRS_THORNHILL", "NATALIA", "NERVOUSRON", "NIGEL", "OLD_MAN1A", "OLD_MAN2", "OMEGA", "ONEIL"},
	{"ORLEANS", "ORTEGA", "PAPER", "PATRICIA", "PRIEST", "PROLSEC", "GANG", "HIC", "HIPSTER", "MEX"},
	{"ROCCOPELOSI", "RUSSIANDRUNK", "SCREEN_WRITER", "SIEMONYETARIAN", "SOLOMON", "STEVEHAINS", "STRETCH", "TALINA", "TANISHA", "TAOCHENG"},
	{"TAOSTRANSLATOR", "TAOSTRANSLATOR_P", "TENNISCOACH", "TERRY", "TOMEPSILON", "TONYA", "TRACYDISANTO", "TRAFFICWARDEN", "TYLERDIX", "WADE"},
	{"ZIMBOR", "DEADHOOKER", "FREEMODE", "MISTY", "STRIPPERLITE", "PROS", "MP_HEADTARGETS", "CLAUDE", "EXARMY", "FAMDD"},
	{"FIBSEC", "FREEMODE", "MARSTON", "NIKO", "SHOPKEEP", "ARMOURED", "NONE", "NONE", "NONE", "NONE"},
	{"NONE", "FEMBARBER", "MAID", "SHOP_HIGH", "SWEATSHOP", "AIRHOSTESS", "BARTENDER", "BAYWATCH", "COP", "FACTORY"},
	{"HOOKER", "HOOKER", "HOOKER", "MIGRANT", "MOVPREM", "RANGER", "SCRUBS", "SHERIFF", "SHOP_LOW", "SHOP_MID"},
	{"STRIPPERLITE", "STRIPPER", "STRIPPER", "SWEATSHOP", "AMMUCOUNTRY", "ARMOURED", "ARMOURED", "AUTOSHOP", "AUTOSHOP", "BOUNCER"},
	{"CHEMSEC", "CIASEC", "CNTRYBAR", "DOCKWORK", "DOCTOR", "FIBOFFICE", "FIBOFFICE", "GAFFER", "GARDENER", "GENTRANSPORT"},
	{"HAIRDRESS", "HIGHSEC", "HIGHSEC", "JANITOR", "LATHANDY", "LIFEINVAD", "LINECOOK", "LSMETRO", "MARIACHI", "MARINE"},
	{"MARINE", "MIGRANT", "ZOMBIE", "MOVPREM", "MOVSPACE", "PARAMEDIC", "PILOT", "PILOT", "POSTAL", "POSTAL"},
	{"PRISGUARD", "SCIENTIST", "SECURITY", "SNOWCOP", "STRPERF", "STRPREACH", "STRVEND", "TRUCKER", "UPS", "UPS"},
	{"BUSKER", "AIRWORKER", "AMMUCITY", "ARMYMECH", "AUTOPSY", "BARMAN", "BAYWATCH", "BLACKOPS", "BLACKOPS", "BUSBOY"},
	{"CHEF", "CLOWN", "CONSTRUCT", "CONSTRUCT", "COP", "DEALER", "DEVINSEC", "DOCKWORK", "DOORMAN", "DWSERVICE"},
	{"DWSERVICE", "FACTORY", "FIREMAN", "GARBAGE", "GRIP", "HWAYCOP", "MARINE", "MARINE", "MARINE", "MIME"},
	{"PESTCONT", "PILOT", "PRISMUSCL", "PRISONER", "RANGER", "ROBBER", "SHERIFF", "SHOP_MASK", "STRVEND", "SWAT"},
	{"USCG", "VALET", "WAITER", "WINCLEAN", "XMECH", "XMECH", "CORPSE", "MIRANDA", "PROMOURN", "MOVIESTAR"},
	{"PROLHOST", "BIKERCHIC", "COMJANE", "CORPSE", "CORPSE", "HOTPOSH", "JEWELASS", "MISTRESS", "POPPYMICH", "PRINCESS"},
	{"SPYACTRESS", "ALDINAPOLI", "BANKMAN", "BIKEHIRE", "FIBARCHITECT", "FILMDIRECTOR", "GLENSTANK", "GRIFF", "JESUS", "JEWELSEC"},
	{"JEWELTHIEF", "MARKFOST", "PARTYTARGET", "PROLSEC", "PROMOURN", "RIVALPAP", "SPYACTOR", "WILLYFIST", "FINGURU", "TAPHILLBILLY"},
	{"TRAMP", "ABNER", "ANTONB", "BABYD", "BAYGOR", "BURGERDRUG", "CHIP", "CYCLIST", "FIBMUGGER", "GUIDO"},
	{"GUNVEND", "HIPPIE", "IMPORAGE", "JUSTIN", "MANI", "MILITARYBUM", "PAPARAZZI", "PARTY", "POGO", "PRISONER"},
	{"BENNY", "G", "VAGSPEAK", "VAGFUN", "BOATSTAFF", "FEMBOATSTAFF", "", "", "", ""}
};

int skinchangerActiveLineIndex = 0;
int skinchangerActiveItemIndex = 0;

bool process_skinchanger_menu()
{
	DWORD waitTime = 150;
	const int lineCount = 70;
	const int itemCount = 10;
	const int itemCountLastLine = 6;
	while (true)
	{
		// 定时菜单绘制，用于激活线路切换后暂停
		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			// draw menu
			char caption[32];
			sprintf_s(caption, "SKIN CHANGER   %d / %d", skinchangerActiveLineIndex + 1, lineCount);
			draw_menu_line(caption, 350.0, 15.0, 18.0, 0.0, 5.0, false, true);
			for (int i = 0; i < itemCount; i++)
				if (strlen(pedModels[skinchangerActiveLineIndex][i]) || strcmp(pedModelNames[skinchangerActiveLineIndex][i], "NONE") == 0)
					draw_menu_line(pedModelNames[skinchangerActiveLineIndex][i], 100.0f, 5.0f, 200.0f, 100.0f + i * 110.0f, 5.0f, i == skinchangerActiveItemIndex, false, false);

			update_features();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;

		bool bSelect, bBack, bUp, bDown, bLeft, bRight;
		get_button_state(&bSelect, &bBack, &bUp, &bDown, &bLeft, &bRight);

		if (bSelect)
		{
			menu_beep();
			DWORD model = GAMEPLAY::GET_HASH_KEY((char*)pedModels[skinchangerActiveLineIndex][skinchangerActiveItemIndex]);
			if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_VALID(model))
			{
				STREAMING::REQUEST_MODEL(model);
				while (!STREAMING::HAS_MODEL_LOADED(model))	WAIT(0);
				//STREAMING::LOAD_ALL_OBJECTS_NOW();
				PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), model);
				//PED::SET_PED_RANDOM_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), FALSE);
				PED::SET_PED_DEFAULT_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID());
				WAIT(0);
				for (int i = 0; i < 12; i++)
					for (int j = 0; j < 100; j++)
					{
						int drawable = rand() % 10;
						int texture = rand() % 10;
						if (PED::IS_PED_COMPONENT_VARIATION_VALID(PLAYER::PLAYER_PED_ID(), i, drawable, texture))
						{
							PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), i, drawable, texture, 0);
							break;
						}
					}
				skinchanger_used = true;
				WAIT(100);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
				waitTime = 200;
			}
		}
		else
			if (bBack)
			{
				menu_beep();
				break;
			}
			else
				if (bRight)
				{
					menu_beep();
					skinchangerActiveItemIndex++;
					int itemsMax = (skinchangerActiveLineIndex == (lineCount - 1)) ? itemCountLastLine : itemCount;
					if (skinchangerActiveItemIndex == itemsMax)
						skinchangerActiveItemIndex = 0;
					waitTime = 100;
				}
				else
					if (bLeft)
					{
						menu_beep();
						if (skinchangerActiveItemIndex == 0)
							skinchangerActiveItemIndex = (skinchangerActiveLineIndex == (lineCount - 1)) ? itemCountLastLine : itemCount;
						skinchangerActiveItemIndex--;
						waitTime = 100;
					}
					else
						if (bUp)
						{
							menu_beep();
							if (skinchangerActiveLineIndex == 0)
								skinchangerActiveLineIndex = lineCount;
							skinchangerActiveLineIndex--;
							waitTime = 200;
						}
						else
							if (bDown)
							{
								menu_beep();
								skinchangerActiveLineIndex++;
								if (skinchangerActiveLineIndex == lineCount)
									skinchangerActiveLineIndex = 0;
								waitTime = 200;
							}
		if (skinchangerActiveLineIndex == (lineCount - 1))
			if (skinchangerActiveItemIndex >= itemCountLastLine)
				skinchangerActiveItemIndex = 0;
	}
	return false;
}

int teleportActiveLineIndex = 0;

bool process_teleport_menu()
{
	const float lineWidth = 250.0;
	const int lineCount = 17;

	std::string caption = "TELEPORT";

	static struct {
		LPCSTR  text;
		float x;
		float y;
		float z;
	} lines[lineCount] = {
			{ "MARKER" },
			{ "MICHAEL'S HOUSE", -852.4f, 160.0f, 65.6f },
			{ "FRANKLIN'S HOUSE", 7.9f, 548.1f, 175.5f },
			{ "TREVOR'S TRAILER", 1985.7f, 3812.2f, 32.2f },
			{ "AIRPORT ENTRANCE", -1034.6f, -2733.6f, 13.8f },
			{ "AIRPORT FIELD", -1336.0f, -3044.0f, 13.9f },
			{ "ELYSIAN ISLAND", 338.2f, -2715.9f, 38.5f },
			{ "JETSAM", 760.4f, -2943.2f, 5.8f },
			{ "STRIPCLUB", 127.4f, -1307.7f, 29.2f },
			{ "ELBURRO HEIGHTS", 1384.0f, -2057.1f, 52.0f },
			{ "FERRIS WHEEL", -1670.7f, -1125.0f, 13.0f },
			{ "CHUMASH", -3192.6f, 1100.0f, 20.2f },
			{ "WINDFARM", 2354.0f, 1830.3f, 101.1f },
			{ "MILITARY BASE", -2047.4f, 3132.1f, 32.8f },
			{ "MCKENZIE AIRFIELD", 2121.7f, 4796.3f, 41.1f },
			{ "DESERT AIRFIELD", 1747.0f, 3273.7f, 41.1f },
			{ "CHILLIAD", 425.4f, 5614.3f, 766.5f }
	};

	DWORD waitTime = 150;
	while (true)
	{
		// 定时菜单绘制，用于激活线路切换后暂停
		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			// 绘图菜单
			draw_menu_line(caption, lineWidth, 15.0, 18.0, 0.0, 5.0, false, true);
			for (int i = 0; i < lineCount; i++)
				if (i != teleportActiveLineIndex)
					draw_menu_line(lines[i].text, lineWidth, 9.0, 60.0 + i * 36.0, 0.0, 9.0, false, false);
			draw_menu_line(lines[teleportActiveLineIndex].text, lineWidth + 1.0, 11.0, 56.0 + teleportActiveLineIndex * 36.0, 0.0, 7.0, true, false);

			update_features();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;

		// 进程按钮
		bool bSelect, bBack, bUp, bDown;
		get_button_state(&bSelect, &bBack, &bUp, &bDown, NULL, NULL);
		if (bSelect)
		{
			menu_beep();

			// 使实体传送
			Entity e = PLAYER::PLAYER_PED_ID();
			if (PED::IS_PED_IN_ANY_VEHICLE(e, 0))
				e = PED::GET_VEHICLE_PED_IS_USING(e);

			// 找点坐标
			Vector3 coords;
			bool success = false;
			if (teleportActiveLineIndex == 0) // 标记
			{
				bool blipFound = false;
				// 搜索标记点
				int blipIterator = UI::_GET_BLIP_INFO_ID_ITERATOR();
				for (Blip i = UI::GET_FIRST_BLIP_INFO_ID(blipIterator); UI::DOES_BLIP_EXIST(i) != 0; i = UI::GET_NEXT_BLIP_INFO_ID(blipIterator))
				{
					if (UI::GET_BLIP_INFO_ID_TYPE(i) == 4)
					{
						coords = UI::GET_BLIP_INFO_ID_COORD(i);
						blipFound = true;
						break;
					}
				}
				if (blipFound)
				{
					// 加载所需的地图区域并检查地面高度
					bool groundFound = false;
					static float groundCheckHeight[] = {
						100.0, 150.0, 50.0, 0.0, 200.0, 250.0, 300.0, 350.0, 400.0,
						450.0, 500.0, 550.0, 600.0, 650.0, 700.0, 750.0, 800.0
					};
					for (int i = 0; i < sizeof(groundCheckHeight) / sizeof(float); i++)
					{
						ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, coords.x, coords.y, groundCheckHeight[i], 0, 0, 1);
						WAIT(100);
						if (GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, groundCheckHeight[i], &coords.z, FALSE))
						{
							groundFound = true;
							coords.z += 3.0;
							break;
						}
					}
					// 如果找不到地面，把Z放在空中，给玩家一个降落伞
					if (!groundFound)
					{
						coords.z = 1000.0;
						WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xFBAB5776, 1, 0);
					}
					success = true;
				}
				else
				{
					set_status_text("map marker isn't set");
				}

			}
			else // 预定义坐标
			{
				coords.x = lines[teleportActiveLineIndex].x;
				coords.y = lines[teleportActiveLineIndex].y;
				coords.z = lines[teleportActiveLineIndex].z;
				success = true;
			}

			// 设置播放器位置
			if (success)
			{
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, coords.x, coords.y, coords.z, 0, 0, 1);
				WAIT(0);
				set_status_text("teleported");
				return true;
			}

			waitTime = 200;
		}
		else
			if (bBack || trainer_switch_pressed())
			{
				menu_beep();
				break;
			}
			else
				if (bUp)
				{
					menu_beep();
					if (teleportActiveLineIndex == 0)
						teleportActiveLineIndex = lineCount;
					teleportActiveLineIndex--;
					waitTime = 150;
				}
				else
					if (bDown)
					{
						menu_beep();
						teleportActiveLineIndex++;
						if (teleportActiveLineIndex == lineCount)
							teleportActiveLineIndex = 0;
						waitTime = 150;
					}
	}
	return false;
}

std::string line_as_str(std::string text, bool* pState)
{
	while (text.size() < 18) text += " ";
	return text + (pState ? (*pState ? " [ON]" : " [OFF]") : "");
}


int activeLineIndexMotorcycle = 0;
int activeLineIndexMotorcycleItem = 0;
LPCSTR motorcycles[2][10] = {
	{"AKUMA","DOUBLE","THRUST","VINDICATOR","HEXER","INNOVATION","SANCHEZ2","SANCHEZ","CARBONRS","BATI"},
	{"BATI2","RUFFIAN","LECTRO","NEMESIS","FAGGIO2","HAKUCHOU","PCJ","VADER","BAGGER","DAEMON"}
	
};
bool process_motorcycle_menu() {
	DWORD waitTime = 150;
	const int lineCount = 2;
	const int itemCount = 10;
	const int itemCountLastLine = 10;
	const float lineWidth = 250.0;
	while (true)
	{
		// timed menu draw, used for pause after active line switch
		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			// draw menu
			draw_menu_line(u8"摩托车", lineWidth, 15.0, 15.0, 25.0, 105.0, false, true);
			char caption2[32];
			sprintf_s(caption2, u8"HOME						%d / %d", activeLineIndexMotorcycle + 1, lineCount);
			about = true;//启用独有约束色
			draw_menu_line(caption2, lineWidth, 2.0, 70.0, 25.0, 5.0, false, false);
			about = false;//关闭独有约束色
			for (int i = 0; i < itemCount; i++)
				if (strlen(motorcycles[activeLineIndexMotorcycle][i]))
					draw_menu_line(motorcycles[activeLineIndexMotorcycle][i], 250.0, 5.0, 91. + i * 27.5, 25.0, 5.0, false, false);
			draw_menu_line(line_as_str(motorcycles[activeLineIndexMotorcycle][activeLineIndexMotorcycleItem], NULL),
				lineWidth, 5.0, 91. + activeLineIndexMotorcycleItem * 27.5, 25.0, 5.0, true, false);
			Bottom = true;
			draw_menu_line(u8"1.58   	   NEVERLOSE 免费		0.2.1", lineWidth, 5.0, 368.5, 25.0, 5.0, false, false);
			Bottom = false;
			update_features();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;

		bool bSelect, bBack, bUp, bDown, bLeft, bRight;
		get_button_state(&bSelect, &bBack, &bUp, &bDown, &bLeft, &bRight);

		if (bSelect)
		{
			menu_beep();
			LPCSTR modelName = motorcycles[activeLineIndexMotorcycle][activeLineIndexMotorcycleItem];
			DWORD model = GAMEPLAY::GET_HASH_KEY((char*)modelName);
			if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_A_VEHICLE(model))
			{
				STREAMING::REQUEST_MODEL(model);
				while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(0);
				Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0, 5.0, 0.0);
				Vehicle veh = VEHICLE::CREATE_VEHICLE(model, coords.x, coords.y, coords.z, 0.0, 1, 1);
				VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);

				if (featureVehmotorcycle)
				{
					ENTITY::SET_ENTITY_HEADING(veh, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
					PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
				}

				WAIT(0);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
				ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&veh);

				char statusText[32];
				sprintf_s(statusText, "%s spawned", modelName);
				set_status_text(statusText);

				return true;
			}
		}
		else
			if (bBack)
			{
				menu_beep();
				break;
			}
			else
				if (bRight)
				{
					//右
				
					menu_beep();
					activeLineIndexMotorcycle++;
					if (activeLineIndexMotorcycle == lineCount)
						activeLineIndexMotorcycle = 0;
					waitTime = 200;
				}
				else
					if (bLeft)
					{
						//左

						menu_beep();
						if (activeLineIndexMotorcycle == 0)
							activeLineIndexMotorcycle = lineCount;
						activeLineIndexMotorcycle--;
						waitTime = 200;
					}
					else
						if (bUp)
						{
							//上
							menu_beep();
							if (activeLineIndexMotorcycleItem == 0)
								activeLineIndexMotorcycleItem = (activeLineIndexMotorcycle == (lineCount - 1)) ? itemCountLastLine : itemCount;
							activeLineIndexMotorcycleItem--;
							waitTime = 100;
						}
						else
							if (bDown)
							{
								//下
								menu_beep();
								activeLineIndexMotorcycleItem++;
								int itemsMax = (activeLineIndexMotorcycle == (lineCount - 1)) ? itemCountLastLine : itemCount;
								if (activeLineIndexMotorcycleItem == itemsMax)
									activeLineIndexMotorcycleItem = 0;
								waitTime = 100;
							}
		if (activeLineIndexMotorcycle == (lineCount - 1))
			if (activeLineIndexMotorcycleItem >= itemCountLastLine)
				activeLineIndexMotorcycleItem = 0;
	}
	return false;
}


int activeLineIndexaircraft = 0;
int activeLineIndexaircraftItem = 0;

LPCSTR aircraft[3][5] = {
	{"CARGOPLANE","JET","LUXOR","LUXOR2","MILJET"},
	{"SHAMAL","VESTRA","MAMMATUS","LAZER","VELUM"},
	{"VELUM2","DODO","TITAN","BESRA","CUBAN800"}
};

bool process_aircraft_menu() {

	DWORD waitTime = 150;
	const int lineCount = 3;
	const int itemCount = 5;
	const int itemCountLastLine = 5;
	const float lineWidth = 250.0;
	while (true)
	{
		// timed menu draw, used for pause after active line switch
		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			// draw menu
			draw_menu_line(u8"飞机", lineWidth, 15.0, 15.0, 25.0, 105.0, false, true);
			char caption2[32];
			sprintf_s(caption2, u8"HOME						%d / %d", activeLineIndexaircraft + 1, lineCount);
			about = true;//启用独有约束色
			draw_menu_line(caption2, lineWidth, 2.0, 70.0, 25.0, 5.0, false, false);
			about = false;//关闭独有约束色
			for (int i = 0; i < itemCount; i++)
				if (strlen(aircraft[activeLineIndexaircraft][i]))
					draw_menu_line(aircraft[activeLineIndexaircraft][i], 250.0, 5.0, 91. + i * 27.5, 25.0, 5.0, false, false);
			draw_menu_line(line_as_str(aircraft[activeLineIndexaircraft][activeLineIndexaircraftItem], NULL),
				lineWidth, 5.0, 91. + activeLineIndexaircraftItem * 27.5, 25.0, 5.0, true, false);
			Bottom = true;
			draw_menu_line(u8"1.58   	   NEVERLOSE 免费		0.2.1", lineWidth, 5.0, 230.0, 25.0, 5.0, false, false);
			Bottom = false;
			update_features();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;

		bool bSelect, bBack, bUp, bDown, bLeft, bRight;
		get_button_state(&bSelect, &bBack, &bUp, &bDown, &bLeft, &bRight);

		if (bSelect)
		{
			menu_beep();
			LPCSTR modelName = aircraft[activeLineIndexaircraft][activeLineIndexaircraftItem];
			DWORD model = GAMEPLAY::GET_HASH_KEY((char*)modelName);
			if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_A_VEHICLE(model))
			{
				STREAMING::REQUEST_MODEL(model);
				while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(0);
				Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0, 5.0, 0.0);
				Vehicle veh = VEHICLE::CREATE_VEHICLE(model, coords.x, coords.y, coords.z, 0.0, 1, 1);
				VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);

				if (featureVenaircraft)
				{
					ENTITY::SET_ENTITY_HEADING(veh, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
					PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
				}

				WAIT(0);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
				ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&veh);

				char statusText[32];
				sprintf_s(statusText, "%s spawned", modelName);
				set_status_text(statusText);

				return true;
			}
		}
		else
			if (bBack)
			{
				menu_beep();
				break;
			}
			else
				if (bRight)
				{
					//右

					menu_beep();
					activeLineIndexaircraft++;
					if (activeLineIndexaircraft == lineCount)
						activeLineIndexaircraft = 0;
					waitTime = 200;
				}
				else
					if (bLeft)
					{
						//左

						menu_beep();
						if (activeLineIndexaircraft == 0)
							activeLineIndexaircraft = lineCount;
						activeLineIndexaircraft--;
						waitTime = 200;
					}
					else
						if (bUp)
						{
							//上
							menu_beep();
							if (activeLineIndexaircraftItem == 0)
								activeLineIndexaircraftItem = (activeLineIndexaircraft == (lineCount - 1)) ? itemCountLastLine : itemCount;
							activeLineIndexaircraftItem--;
							waitTime = 100;
						}
						else
							if (bDown)
							{
								//下
								menu_beep();
								activeLineIndexaircraftItem++;
								int itemsMax = (activeLineIndexaircraft == (lineCount - 1)) ? itemCountLastLine : itemCount;
								if (activeLineIndexaircraftItem == itemsMax)
									activeLineIndexaircraftItem = 0;
								waitTime = 100;
							}
		if (activeLineIndexaircraft == (lineCount - 1))
			if (activeLineIndexaircraftItem >= itemCountLastLine)
				activeLineIndexaircraftItem = 0;
	}
	return false;
}


int activeLineIndexhelicopter = 0;
int activeLineIndexhelicopterIteem = 0;

LPCSTR helicopter[3][5] = {
	{"BLIMP","BLIMP2","SAVAGE","SWIFT","SWIFT2"},
	{"SKYLIFT","FROGGER","FROGGER2","BUZZARD2","BUZZARD"},
	{"ANNIHILATOR","CARGOBOB","CARGOBOB2","CARGOBOB3","MAVERICK"}
};

bool process_helicopter_menu() {
	DWORD waitTime = 150;
	const int lineCount = 3;
	const int itemCount = 5;
	const int itemCountLastLine = 5;
	const float lineWidth = 250.0;
	while (true)
	{
		// timed menu draw, used for pause after active line switch
		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			// draw menu
			draw_menu_line(u8"直升机", lineWidth, 15.0, 15.0, 25.0, 105.0, false, true);
			char caption2[32];
			sprintf_s(caption2, u8"HOME						%d / %d", activeLineIndexhelicopter + 1, lineCount);
			about = true;//启用独有约束色
			draw_menu_line(caption2, lineWidth, 2.0, 70.0, 25.0, 5.0, false, false);
			about = false;//关闭独有约束色
			for (int i = 0; i < itemCount; i++)
				if (strlen(helicopter[activeLineIndexhelicopter][i]))
					draw_menu_line(helicopter[activeLineIndexhelicopter][i], 250.0, 5.0, 91. + i * 27.5, 25.0, 5.0, false, false);
			draw_menu_line(line_as_str(helicopter[activeLineIndexhelicopter][activeLineIndexhelicopterIteem], NULL),
				lineWidth, 5.0, 91. + activeLineIndexhelicopterIteem * 27.5, 25.0, 5.0, true, false);
			Bottom = true;
			draw_menu_line(u8"1.58   	   NEVERLOSE 免费		0.2.1", lineWidth, 5.0, 230.0, 25.0, 5.0, false, false);
			Bottom = false;
			update_features();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;

		bool bSelect, bBack, bUp, bDown, bLeft, bRight;
		get_button_state(&bSelect, &bBack, &bUp, &bDown, &bLeft, &bRight);

		if (bSelect)
		{
			menu_beep();
			LPCSTR modelName = helicopter[activeLineIndexhelicopter][activeLineIndexhelicopterIteem];
			DWORD model = GAMEPLAY::GET_HASH_KEY((char*)modelName);
			if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_A_VEHICLE(model))
			{
				STREAMING::REQUEST_MODEL(model);
				while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(0);
				Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0, 5.0, 0.0);
				Vehicle veh = VEHICLE::CREATE_VEHICLE(model, coords.x, coords.y, coords.z, 0.0, 1, 1);
				VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);

				if (featureVenaircraft)
				{
					ENTITY::SET_ENTITY_HEADING(veh, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
					PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
				}

				WAIT(0);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
				ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&veh);

				char statusText[32];
				sprintf_s(statusText, "%s spawned", modelName);
				set_status_text(statusText);

				return true;
			}
		}
		else
			if (bBack)
			{
				menu_beep();
				break;
			}
			else
				if (bRight)
				{
					//右

					menu_beep();
					activeLineIndexhelicopter++;
					if (activeLineIndexhelicopter == lineCount)
						activeLineIndexhelicopter = 0;
					waitTime = 200;
				}
				else
					if (bLeft)
					{
						//左

						menu_beep();
						if (activeLineIndexhelicopter == 0)
							activeLineIndexhelicopter = lineCount;
						activeLineIndexhelicopter--;
						waitTime = 200;
					}
					else
						if (bUp)
						{
							//上
							menu_beep();
							if (activeLineIndexhelicopterIteem == 0)
								activeLineIndexhelicopterIteem = (activeLineIndexhelicopter == (lineCount - 1)) ? itemCountLastLine : itemCount;
							activeLineIndexhelicopterIteem--;
							waitTime = 100;
						}
						else
							if (bDown)
							{
								//下
								menu_beep();
								activeLineIndexhelicopterIteem++;
								int itemsMax = (activeLineIndexhelicopter == (lineCount - 1)) ? itemCountLastLine : itemCount;
								if (activeLineIndexhelicopterIteem == itemsMax)
									activeLineIndexhelicopterIteem = 0;
								waitTime = 100;
							}
		if (activeLineIndexhelicopter == (lineCount - 1))
			if (activeLineIndexhelicopterIteem >= itemCountLastLine)
				activeLineIndexhelicopterIteem = 0;
	}
	return false;

}

int activeLineIndexaship = 0;
int activeLineIndexashipItem = 0;

LPCSTR aship[3][5] = {
	{"MARQUIS","SUBMERSIBLE2","DINGHY2","DINGHY3","DINGHY"},
	{"SPEEDER","JETMAX","PREDATOR","SQUALO","SUNTRAP"},
	{"TROPIC","SEASHARK","SEASHARK2","SUBMERSIBLE","TORO"}
};

bool process_aship_menu() {
	DWORD waitTime = 150;
	const int lineCount = 3;
	const int itemCount = 5;
	const int itemCountLastLine = 5;
	const float lineWidth = 250.0;
	while (true)
	{
		// timed menu draw, used for pause after active line switch
		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			// draw menu
			draw_menu_line(u8"船舶", lineWidth, 15.0, 15.0, 25.0, 105.0, false, true);
			char caption2[32];
			sprintf_s(caption2, u8"HOME						%d / %d", activeLineIndexaship + 1, lineCount);
			about = true;//启用独有约束色
			draw_menu_line(caption2, lineWidth, 2.0, 70.0, 25.0, 5.0, false, false);
			about = false;//关闭独有约束色
			for (int i = 0; i < itemCount; i++)
				if (strlen(aship[activeLineIndexaship][i]))
					draw_menu_line(aship[activeLineIndexaship][i], 250.0, 5.0, 91. + i * 27.5, 25.0, 5.0, false, false);
			draw_menu_line(line_as_str(aship[activeLineIndexaship][activeLineIndexashipItem], NULL),
				lineWidth, 5.0, 91. + activeLineIndexashipItem * 27.5, 25.0, 5.0, true, false);
			Bottom = true;
			draw_menu_line(u8"1.58   	   NEVERLOSE 免费		0.2.1", lineWidth, 5.0, 230.0, 25.0, 5.0, false, false);
			Bottom = false;
			update_features();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;

		bool bSelect, bBack, bUp, bDown, bLeft, bRight;
		get_button_state(&bSelect, &bBack, &bUp, &bDown, &bLeft, &bRight);

		if (bSelect)
		{
			menu_beep();
			LPCSTR modelName = aship[activeLineIndexaship][activeLineIndexashipItem];
			DWORD model = GAMEPLAY::GET_HASH_KEY((char*)modelName);
			if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_A_VEHICLE(model))
			{
				STREAMING::REQUEST_MODEL(model);
				while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(0);
				Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0, 5.0, 0.0);
				Vehicle veh = VEHICLE::CREATE_VEHICLE(model, coords.x, coords.y, coords.z, 0.0, 1, 1);
				VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);

				if (featureVenaircraft)
				{
					ENTITY::SET_ENTITY_HEADING(veh, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
					PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
				}

				WAIT(0);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
				ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&veh);

				char statusText[32];
				sprintf_s(statusText, "%s spawned", modelName);
				set_status_text(statusText);

				return true;
			}
		}
		else
			if (bBack)
			{
				menu_beep();
				break;
			}
			else
				if (bRight)
				{
					//右

					menu_beep();
					activeLineIndexaship++;
					if (activeLineIndexaship == lineCount)
						activeLineIndexaship = 0;
					waitTime = 200;
				}
				else
					if (bLeft)
					{
						//左

						menu_beep();
						if (activeLineIndexaship == 0)
							activeLineIndexaship = lineCount;
						activeLineIndexaship--;
						waitTime = 200;
					}
					else
						if (bUp)
						{
							//上
							menu_beep();
							if (activeLineIndexashipItem == 0)
								activeLineIndexashipItem = (activeLineIndexaship == (lineCount - 1)) ? itemCountLastLine : itemCount;
							activeLineIndexashipItem--;
							waitTime = 100;
						}
						else
							if (bDown)
							{
								//下
								menu_beep();
								activeLineIndexashipItem++;
								int itemsMax = (activeLineIndexaship == (lineCount - 1)) ? itemCountLastLine : itemCount;
								if (activeLineIndexashipItem == itemsMax)
									activeLineIndexashipItem = 0;
								waitTime = 100;
							}
		if (activeLineIndexaship == (lineCount - 1))
			if (activeLineIndexashipItem >= itemCountLastLine)
				activeLineIndexashipItem = 0;
	}
	return false;
}


int activeLineIndexBicycle = 0;
int activeLineIndexBicycleItem = 0;

LPCSTR Bicycle[1][7] = {
	{"BMX","CRUISER","TRIBIKE2","FIXTER","SCORCHER","TRIBIKE3","TRIBIKE"}
};

bool process_Bicycle_menu() {
	DWORD waitTime = 150;
	const int lineCount = 1;
	const int itemCount = 7;
	const int itemCountLastLine = 7;
	const float lineWidth = 250.0;
	while (true)
	{
		// timed menu draw, used for pause after active line switch
		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			// draw menu
			draw_menu_line(u8"自行车", lineWidth, 15.0, 15.0, 25.0, 105.0, false, true);
			char caption2[32];
			sprintf_s(caption2, u8"HOME						%d / %d", activeLineIndexBicycle + 1, lineCount);
			about = true;//启用独有约束色
			draw_menu_line(caption2, lineWidth, 2.0, 70.0, 25.0, 5.0, false, false);
			about = false;//关闭独有约束色
			for (int i = 0; i < itemCount; i++)
				if (strlen(Bicycle[activeLineIndexBicycle][i]))
					draw_menu_line(Bicycle[activeLineIndexBicycle][i], 250.0, 5.0, 91. + i * 27.5, 25.0, 5.0, false, false);
			draw_menu_line(line_as_str(Bicycle[activeLineIndexBicycle][activeLineIndexBicycleItem], NULL),
				lineWidth, 5.0, 91. + activeLineIndexBicycleItem * 27.5, 25.0, 5.0, true, false);
			Bottom = true;
			draw_menu_line(u8"1.58   	   NEVERLOSE 免费		0.2.1", lineWidth, 5.0, 285.5, 25.0, 5.0, false, false);
			Bottom = false;
			update_features();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;

		bool bSelect, bBack, bUp, bDown, bLeft, bRight;
		get_button_state(&bSelect, &bBack, &bUp, &bDown, &bLeft, &bRight);

		if (bSelect)
		{
			menu_beep();
			LPCSTR modelName = Bicycle[activeLineIndexBicycle][activeLineIndexBicycleItem];
			DWORD model = GAMEPLAY::GET_HASH_KEY((char*)modelName);
			if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_A_VEHICLE(model))
			{
				STREAMING::REQUEST_MODEL(model);
				while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(0);
				Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0, 5.0, 0.0);
				Vehicle veh = VEHICLE::CREATE_VEHICLE(model, coords.x, coords.y, coords.z, 0.0, 1, 1);
				VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);

				if (featureVenaircraft)
				{
					ENTITY::SET_ENTITY_HEADING(veh, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
					PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
				}

				WAIT(0);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
				ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&veh);

				char statusText[32];
				sprintf_s(statusText, "%s spawned", modelName);
				set_status_text(statusText);

				return true;
			}
		}
		else
			if (bBack)
			{
				menu_beep();
				break;
			}
			else
				if (bRight)
				{
					//右

					menu_beep();
					activeLineIndexBicycle++;
					if (activeLineIndexBicycle == lineCount)
						activeLineIndexBicycle = 0;
					waitTime = 200;
				}
				else
					if (bLeft)
					{
						//左

						menu_beep();
						if (activeLineIndexBicycle == 0)
							activeLineIndexBicycle = lineCount;
						activeLineIndexBicycle--;
						waitTime = 200;
					}
					else
						if (bUp)
						{
							//上
							menu_beep();
							if (activeLineIndexBicycleItem == 0)
								activeLineIndexBicycleItem = (activeLineIndexBicycle == (lineCount - 1)) ? itemCountLastLine : itemCount;
							activeLineIndexBicycleItem--;
							waitTime = 100;
						}
						else
							if (bDown)
							{
								//下
								menu_beep();
								activeLineIndexBicycleItem++;
								int itemsMax = (activeLineIndexBicycle == (lineCount - 1)) ? itemCountLastLine : itemCount;
								if (activeLineIndexBicycleItem == itemsMax)
									activeLineIndexBicycleItem = 0;
								waitTime = 100;
							}
		if (activeLineIndexBicycle == (lineCount - 1))
			if (activeLineIndexBicycleItem >= itemCountLastLine)
				activeLineIndexBicycleItem = 0;
	}
	return false;
}

int activeLineIndexSuperCar = 0;
int activeLineIndexSuperCarItem = 0;

LPCSTR SuperCar[1][10] = {
	{"VOLTIC","CHEETAH","TURISMOR","ENTITYXF","INFERNUS","VACCA","ZENTORNO","ADDER","BULLET","OSIRIS"}
};

bool process_SuperCar_menu() {
	DWORD waitTime = 150;
	const int lineCount = 1;
	const int itemCount = 10;
	const int itemCountLastLine = 10;
	const float lineWidth = 250.0;
	while (true)
	{
		// timed menu draw, used for pause after active line switch
		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			// draw menu
			draw_menu_line(u8"超级跑车", lineWidth, 15.0, 15.0, 25.0, 105.0, false, true);
			char caption2[32];
			sprintf_s(caption2, u8"HOME						%d / %d", activeLineIndexSuperCar + 1, lineCount);
			about = true;//启用独有约束色
			draw_menu_line(caption2, lineWidth, 2.0, 70.0, 25.0, 5.0, false, false);
			about = false;//关闭独有约束色
			for (int i = 0; i < itemCount; i++)
				if (strlen(SuperCar[activeLineIndexSuperCar][i]))
					draw_menu_line(SuperCar[activeLineIndexSuperCar][i], 250.0, 5.0, 91. + i * 27.5, 25.0, 5.0, false, false);
			draw_menu_line(line_as_str(SuperCar[activeLineIndexSuperCar][activeLineIndexSuperCarItem], NULL),
				lineWidth, 5.0, 91. + activeLineIndexSuperCarItem * 27.5, 25.0, 5.0, true, false);
			Bottom = true;
			draw_menu_line(u8"1.58   	   NEVERLOSE 免费		0.2.1", lineWidth, 5.0, 368.5, 25.0, 5.0, false, false);
			Bottom = false;
			update_features();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;

		bool bSelect, bBack, bUp, bDown, bLeft, bRight;
		get_button_state(&bSelect, &bBack, &bUp, &bDown, &bLeft, &bRight);

		if (bSelect)
		{
			menu_beep();
			LPCSTR modelName = SuperCar[activeLineIndexSuperCar][activeLineIndexSuperCarItem];
			DWORD model = GAMEPLAY::GET_HASH_KEY((char*)modelName);
			if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_A_VEHICLE(model))
			{
				STREAMING::REQUEST_MODEL(model);
				while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(0);
				Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0, 5.0, 0.0);
				Vehicle veh = VEHICLE::CREATE_VEHICLE(model, coords.x, coords.y, coords.z, 0.0, 1, 1);
				VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);

				if (featureVenaircraft)
				{
					ENTITY::SET_ENTITY_HEADING(veh, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
					PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
				}

				WAIT(0);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
				ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&veh);

				char statusText[32];
				sprintf_s(statusText, "%s spawned", modelName);
				set_status_text(statusText);

				return true;
			}
		}
		else
			if (bBack)
			{
				menu_beep();
				break;
			}
			else
				if (bRight)
				{
					//右

					menu_beep();
					activeLineIndexSuperCar++;
					if (activeLineIndexSuperCar == lineCount)
						activeLineIndexSuperCar = 0;
					waitTime = 200;
				}
				else
					if (bLeft)
					{
						//左

						menu_beep();
						if (activeLineIndexSuperCar == 0)
							activeLineIndexSuperCar = lineCount;
						activeLineIndexSuperCar--;
						waitTime = 200;
					}
					else
						if (bUp)
						{
							//上
							menu_beep();
							if (activeLineIndexSuperCarItem == 0)
								activeLineIndexSuperCarItem = (activeLineIndexSuperCar == (lineCount - 1)) ? itemCountLastLine : itemCount;
							activeLineIndexSuperCarItem--;
							waitTime = 100;
						}
						else
							if (bDown)
							{
								//下
								menu_beep();
								activeLineIndexSuperCarItem++;
								int itemsMax = (activeLineIndexSuperCar == (lineCount - 1)) ? itemCountLastLine : itemCount;
								if (activeLineIndexSuperCarItem == itemsMax)
									activeLineIndexSuperCarItem = 0;
								waitTime = 100;
							}
		if (activeLineIndexSuperCar == (lineCount - 1))
			if (activeLineIndexSuperCarItem >= itemCountLastLine)
				activeLineIndexSuperCarItem = 0;
	}
	return false;
}


int activeLineIndexSportsCar = 0;
int activeLineIndexSportsCarItem = 0;

LPCSTR SportsCar[4][7] = {
	{"ALPHA","ELEGY2","FELTZER2","SCHWARZER","SURANO","BANSHEE","BUFFALO"},
	{"BUFFALO2","BUFFALO3","MASSACRO","MASSACRO2","RAPIDGT","RAPIDGT2","BLISTA2"},
	{"BLISTA3","JESTER","JESTER2","CARBONIZZARE","KHAMELION","COQUETTE","FUTO"},
	{"SULTAN","FUROREGT","PENUMBRA","NINEF","NINEF2","COMET2","FUSILADE"}
};

bool process_SportsCar_menu() {
	DWORD waitTime = 150;
	const int lineCount = 1;
	const int itemCount = 7;
	const int itemCountLastLine = 7;
	const float lineWidth = 250.0;
	while (true)
	{
		
		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			// draw menu
			draw_menu_line(u8"跑车", lineWidth, 15.0, 15.0, 25.0, 105.0, false, true);
			char caption2[32];
			sprintf_s(caption2, u8"HOME						%d / %d", activeLineIndexSportsCar + 1, lineCount);
			about = true;//启用独有约束色
			draw_menu_line(caption2, lineWidth, 2.0, 70.0, 25.0, 5.0, false, false);
			about = false;//关闭独有约束色
			for (int i = 0; i < itemCount; i++)
				if (strlen(SportsCar[activeLineIndexSportsCar][i]))
					draw_menu_line(SportsCar[activeLineIndexSportsCar][i], 250.0, 5.0, 91. + i * 27.5, 25.0, 5.0, false, false);
			draw_menu_line(line_as_str(SportsCar[activeLineIndexSportsCar][activeLineIndexSportsCarItem], NULL),
				lineWidth, 5.0, 91. + activeLineIndexSportsCarItem * 27.5, 25.0, 5.0, true, false);
			Bottom = true;
			draw_menu_line(u8"1.58   	   NEVERLOSE 免费		0.2.1", lineWidth, 5.0, 285.5, 25.0, 5.0, false, false);
			Bottom = false;
			update_features();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;

		bool bSelect, bBack, bUp, bDown, bLeft, bRight;
		get_button_state(&bSelect, &bBack, &bUp, &bDown, &bLeft, &bRight);

		if (bSelect)
		{
			menu_beep();
			LPCSTR modelName = SportsCar[activeLineIndexSportsCar][activeLineIndexSportsCarItem];
			DWORD model = GAMEPLAY::GET_HASH_KEY((char*)modelName);
			if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_A_VEHICLE(model))
			{
				STREAMING::REQUEST_MODEL(model);
				while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(0);
				Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0, 5.0, 0.0);
				Vehicle veh = VEHICLE::CREATE_VEHICLE(model, coords.x, coords.y, coords.z, 0.0, 1, 1);
				VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);

				if (featureVenaircraft)
				{
					ENTITY::SET_ENTITY_HEADING(veh, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
					PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
				}

				WAIT(0);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
				ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&veh);

				char statusText[32];
				sprintf_s(statusText, "%s spawned", modelName);
				set_status_text(statusText);

				return true;
			}
		}
		else
			if (bBack)
			{
				menu_beep();
				break;
			}
			else
				if (bRight)
				{
					//右

					menu_beep();
					activeLineIndexSportsCar++;
					if (activeLineIndexSportsCar == lineCount)
						activeLineIndexSportsCar = 0;
					waitTime = 200;
				}
				else
					if (bLeft)
					{
						//左

						menu_beep();
						if (activeLineIndexSportsCar == 0)
							activeLineIndexSportsCar = lineCount;
						activeLineIndexSportsCar--;
						waitTime = 200;
					}
					else
						if (bUp)
						{
							//上
							menu_beep();
							if (activeLineIndexSportsCarItem == 0)
								activeLineIndexSportsCarItem = (activeLineIndexSportsCar == (lineCount - 1)) ? itemCountLastLine : itemCount;
							activeLineIndexSportsCarItem--;
							waitTime = 100;
						}
						else
							if (bDown)
							{
								//下
								menu_beep();
								activeLineIndexSportsCarItem++;
								int itemsMax = (activeLineIndexSportsCar == (lineCount - 1)) ? itemCountLastLine : itemCount;
								if (activeLineIndexSportsCarItem == itemsMax)
									activeLineIndexSportsCarItem = 0;
								waitTime = 100;
							}
		if (activeLineIndexSportsCar == (lineCount - 1))
			if (activeLineIndexSportsCarItem >= itemCountLastLine)
				activeLineIndexSportsCarItem = 0;
	}
	return false;
}



int activeLineIndexJindianSportsCar = 0;
int activeLineIndexJindianSportsCarItem = 0;

LPCSTR JinDianSportsCar[3][5] = {
	{"MANANA","BTYPE","TORNADO","TORNADO3","TORNADO2"},
	{"TORNADO4","JB700","STINGER","STINGERGT","COQUETTE2"},
	{"PIGALLE","MONROE","ZTYPE","PEYOTE","FELTZER3"}
};

bool process_jindianSportsCar_menu() {
	DWORD waitTime = 150;
	const int lineCount = 3;
	const int itemCount = 5;
	const int itemCountLastLine = 5;
	const float lineWidth = 250.0;

	while (true)
	{

		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			// draw menu
			draw_menu_line(u8"经典跑车", lineWidth, 15.0, 15.0, 25.0, 105.0, false, true);
			char caption2[32];
			sprintf_s(caption2, u8"HOME						%d / %d", activeLineIndexJindianSportsCar + 1, lineCount);
			about = true;//启用独有约束色
			draw_menu_line(caption2, lineWidth, 2.0, 70.0, 25.0, 5.0, false, false);
			about = false;//关闭独有约束色
			for (int i = 0; i < itemCount; i++)
				if (strlen(JinDianSportsCar[activeLineIndexJindianSportsCar][i]))
					draw_menu_line(JinDianSportsCar[activeLineIndexJindianSportsCar][i], 250.0, 5.0, 91. + i * 27.5, 25.0, 5.0, false, false);
			draw_menu_line(line_as_str(JinDianSportsCar[activeLineIndexJindianSportsCar][activeLineIndexJindianSportsCarItem], NULL),
				lineWidth, 5.0, 91. + activeLineIndexJindianSportsCarItem * 27.5, 25.0, 5.0, true, false);
			Bottom = true;
			draw_menu_line(u8"1.58   	   NEVERLOSE 免费		0.2.1", lineWidth, 5.0, 230.0, 25.0, 5.0, false, false);
			Bottom = false;
			update_features();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;

		bool bSelect, bBack, bUp, bDown, bLeft, bRight;
		get_button_state(&bSelect, &bBack, &bUp, &bDown, &bLeft, &bRight);

		if (bSelect)
		{
			menu_beep();
			LPCSTR modelName = JinDianSportsCar[activeLineIndexJindianSportsCar][activeLineIndexJindianSportsCarItem];
			DWORD model = GAMEPLAY::GET_HASH_KEY((char*)modelName);
			if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_A_VEHICLE(model))
			{
				STREAMING::REQUEST_MODEL(model);
				while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(0);
				Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0, 5.0, 0.0);
				Vehicle veh = VEHICLE::CREATE_VEHICLE(model, coords.x, coords.y, coords.z, 0.0, 1, 1);
				VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);

				if (featureVenaircraft)
				{
					ENTITY::SET_ENTITY_HEADING(veh, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
					PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
				}

				WAIT(0);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
				ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&veh);

				char statusText[32];
				sprintf_s(statusText, "%s spawned", modelName);
				set_status_text(statusText);

				return true;
			}
		}
		else
			if (bBack)
			{
				menu_beep();
				break;
			}
			else
				if (bRight)
				{
					//右

					menu_beep();
					activeLineIndexJindianSportsCar++;
					if (activeLineIndexJindianSportsCar == lineCount)
						activeLineIndexJindianSportsCar = 0;
					waitTime = 200;
				}
				else
					if (bLeft)
					{
						//左

						menu_beep();
						if (activeLineIndexJindianSportsCar == 0)
							activeLineIndexJindianSportsCar = lineCount;
						activeLineIndexJindianSportsCar--;
						waitTime = 200;
					}
					else
						if (bUp)
						{
							//上
							menu_beep();
							if (activeLineIndexJindianSportsCarItem == 0)
								activeLineIndexJindianSportsCarItem = (activeLineIndexJindianSportsCar == (lineCount - 1)) ? itemCountLastLine : itemCount;
							activeLineIndexJindianSportsCarItem--;
							waitTime = 100;
						}
						else
							if (bDown)
							{
								//下
								menu_beep();
								activeLineIndexJindianSportsCarItem++;
								int itemsMax = (activeLineIndexJindianSportsCar == (lineCount - 1)) ? itemCountLastLine : itemCount;
								if (activeLineIndexJindianSportsCarItem == itemsMax)
									activeLineIndexJindianSportsCarItem = 0;
								waitTime = 100;
							}
		if (activeLineIndexJindianSportsCar == (lineCount - 1))
			if (activeLineIndexJindianSportsCarItem >= itemCountLastLine)
				activeLineIndexJindianSportsCarItem = 0;
	}
	return false;
}

int activeLineIndexCoupe = 0;
int activeLineIndexCoupeItem = 0;

LPCSTR Coupe[2][5] = {
	{"EXEMPLAR","COGCABRIO","FELON","FELON2","F620"},
	{"JACKAL","SENTINEL","SENTINEL2","ZION","ZION2"}
};

bool process_Coupe_menu() {
	DWORD waitTime = 150;
	const int lineCount = 2;
	const int itemCount = 5;
	const int itemCountLastLine = 5;
	const float lineWidth = 250.0;

	while (true)
	{

		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			// draw menu
			draw_menu_line(u8"轿跑车", lineWidth, 15.0, 15.0, 25.0, 105.0, false, true);
			char caption2[32];
			sprintf_s(caption2, u8"HOME						%d / %d", activeLineIndexCoupe + 1, lineCount);
			about = true;//启用独有约束色
			draw_menu_line(caption2, lineWidth, 2.0, 70.0, 25.0, 5.0, false, false);
			about = false;//关闭独有约束色
			for (int i = 0; i < itemCount; i++)
				if (strlen(Coupe[activeLineIndexCoupe][i]))
					draw_menu_line(Coupe[activeLineIndexCoupe][i], 250.0, 5.0, 91. + i * 27.5, 25.0, 5.0, false, false);
			draw_menu_line(line_as_str(Coupe[activeLineIndexCoupe][activeLineIndexCoupeItem], NULL),
				lineWidth, 5.0, 91. + activeLineIndexCoupeItem * 27.5, 25.0, 5.0, true, false);
			Bottom = true;
			draw_menu_line(u8"1.58   	   NEVERLOSE 免费		0.2.1", lineWidth, 5.0, 230.0, 25.0, 5.0, false, false);
			Bottom = false;
			update_features();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;

		bool bSelect, bBack, bUp, bDown, bLeft, bRight;
		get_button_state(&bSelect, &bBack, &bUp, &bDown, &bLeft, &bRight);

		if (bSelect)
		{
			menu_beep();
			LPCSTR modelName = Coupe[activeLineIndexCoupe][activeLineIndexCoupeItem];
			DWORD model = GAMEPLAY::GET_HASH_KEY((char*)modelName);
			if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_A_VEHICLE(model))
			{
				STREAMING::REQUEST_MODEL(model);
				while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(0);
				Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0, 5.0, 0.0);
				Vehicle veh = VEHICLE::CREATE_VEHICLE(model, coords.x, coords.y, coords.z, 0.0, 1, 1);
				VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);

				if (featureVenaircraft)
				{
					ENTITY::SET_ENTITY_HEADING(veh, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
					PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
				}

				WAIT(0);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
				ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&veh);

				char statusText[32];
				sprintf_s(statusText, "%s spawned", modelName);
				set_status_text(statusText);

				return true;
			}
		}
		else
			if (bBack)
			{
				menu_beep();
				break;
			}
			else
				if (bRight)
				{
					//右

					menu_beep();
					activeLineIndexCoupe++;
					if (activeLineIndexCoupe == lineCount)
						activeLineIndexCoupe = 0;
					waitTime = 200;
				}
				else
					if (bLeft)
					{
						//左

						menu_beep();
						if (activeLineIndexCoupe == 0)
							activeLineIndexCoupe = lineCount;
						activeLineIndexCoupe--;
						waitTime = 200;
					}
					else
						if (bUp)
						{
							//上
							menu_beep();
							if (activeLineIndexCoupeItem == 0)
								activeLineIndexCoupeItem = (activeLineIndexCoupe == (lineCount - 1)) ? itemCountLastLine : itemCount;
							activeLineIndexCoupeItem--;
							waitTime = 100;
						}
						else
							if (bDown)
							{
								//下
								menu_beep();
								activeLineIndexCoupeItem++;
								int itemsMax = (activeLineIndexCoupe == (lineCount - 1)) ? itemCountLastLine : itemCount;
								if (activeLineIndexCoupeItem == itemsMax)
									activeLineIndexCoupeItem = 0;
								waitTime = 100;
							}
		if (activeLineIndexCoupe == (lineCount - 1))
			if (activeLineIndexCoupeItem >= itemCountLastLine)
				activeLineIndexCoupeItem = 0;
	}
	return false;
}

int activeLineIndexMuscle = 0;
int activeLineIndexMuscleItem = 0;

LPCSTR Muscle[3][7] = {
	{"BUCCANEER","GAUNTLET","GAUNTLET2","PICADOR","SABREGT","STALION","STALION2"},
	{"VIGERO","VOODOO2","DUKES","PHOENIX","RUINER","BLADE","DOMINATOR"},
	{"DOMINATOR2","HOTKNIFE","SLAMVAN","SLAMVAN2","CHINO","VIRGO","COQUETTE3"}
};

bool process_Muscle_menu() {
	DWORD waitTime = 150;
	const int lineCount = 3;
	const int itemCount = 7;
	const int itemCountLastLine = 7;
	const float lineWidth = 250.0;

	while (true)
	{

		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			// draw menu
			draw_menu_line(u8"肌肉车", lineWidth, 15.0, 15.0, 25.0, 105.0, false, true);
			char caption2[32];
			sprintf_s(caption2, u8"HOME						%d / %d", activeLineIndexMuscle + 1, lineCount);
			about = true;//启用独有约束色
			draw_menu_line(caption2, lineWidth, 2.0, 70.0, 25.0, 5.0, false, false);
			about = false;//关闭独有约束色
			for (int i = 0; i < itemCount; i++)
				if (strlen(Muscle[activeLineIndexMuscle][i]))
					draw_menu_line(Muscle[activeLineIndexMuscle][i], 250.0, 5.0, 91. + i * 27.5, 25.0, 5.0, false, false);
			draw_menu_line(line_as_str(Muscle[activeLineIndexMuscle][activeLineIndexMuscleItem], NULL),
				lineWidth, 5.0, 91. + activeLineIndexMuscleItem * 27.5, 25.0, 5.0, true, false);
			Bottom = true;
			draw_menu_line(u8"1.58   	   NEVERLOSE 免费		0.2.1", lineWidth, 5.0, 285.5, 25.0, 5.0, false, false);
			Bottom = false;
			update_features();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;

		bool bSelect, bBack, bUp, bDown, bLeft, bRight;
		get_button_state(&bSelect, &bBack, &bUp, &bDown, &bLeft, &bRight);

		if (bSelect)
		{
			menu_beep();
			LPCSTR modelName = Muscle[activeLineIndexMuscle][activeLineIndexMuscleItem];
			DWORD model = GAMEPLAY::GET_HASH_KEY((char*)modelName);
			if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_A_VEHICLE(model))
			{
				STREAMING::REQUEST_MODEL(model);
				while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(0);
				Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0, 5.0, 0.0);
				Vehicle veh = VEHICLE::CREATE_VEHICLE(model, coords.x, coords.y, coords.z, 0.0, 1, 1);
				VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);
				
				if (featureVenaircraft)
				{
					ENTITY::SET_ENTITY_HEADING(veh, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
					PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
				}

				WAIT(0);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
				ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&veh);

				char statusText[32];
				sprintf_s(statusText, "%s spawned", modelName);
				set_status_text(statusText);

				return true;
			}
		}
		else
			if (bBack)
			{
				menu_beep();
				break;
			}
			else
				if (bRight)
				{
					//右

					menu_beep();
					activeLineIndexMuscle++;
					if (activeLineIndexMuscle == lineCount)
						activeLineIndexMuscle = 0;
					waitTime = 200;
				}
				else
					if (bLeft)
					{
						//左

						menu_beep();
						if (activeLineIndexMuscle == 0)
							activeLineIndexMuscle = lineCount;
						activeLineIndexMuscle--;
						waitTime = 200;
					}
					else
						if (bUp)
						{
							//上
							menu_beep();
							if (activeLineIndexMuscleItem == 0)
								activeLineIndexMuscleItem = (activeLineIndexMuscle == (lineCount - 1)) ? itemCountLastLine : itemCount;
							activeLineIndexMuscleItem--;
							waitTime = 100;
						}
						else
							if (bDown)
							{
								//下
								menu_beep();
								activeLineIndexMuscleItem++;
								int itemsMax = (activeLineIndexMuscle == (lineCount - 1)) ? itemCountLastLine : itemCount;
								if (activeLineIndexMuscleItem == itemsMax)
									activeLineIndexMuscleItem = 0;
								waitTime = 100;
							}
		if (activeLineIndexMuscle == (lineCount - 1))
			if (activeLineIndexMuscleItem >= itemCountLastLine)
				activeLineIndexMuscleItem = 0;
	}
	return false;
}

int activeLineIndexCrossCountry = 0;
int activeLineIndexCrossCountryItem = 0;

LPCSTR CrossCountry[3][7] = {
	{"DUBSTA3","BIFTA","BFINJECTION","DUNE","DLOADER","DUNE2","BODHI2"},
	{"KALAHARI","MESA3","MARSHALL","RANCHERXL","RANCHERXL2","REBEL2","REBEL"},
	{"BLAZER","BLAZER3","BLAZER2","SANDKING2","SANDKING","MONSTER","BRAWLER"}
};

bool process_CrossCountry_menu() {
	DWORD waitTime = 150;
	const int lineCount = 3;
	const int itemCount = 7;
	const int itemCountLastLine = 7;
	const float lineWidth = 250.0;

	while (true)
	{

		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			// draw menu
			draw_menu_line(u8"越野车", lineWidth, 15.0, 15.0, 25.0, 105.0, false, true);
			char caption2[32];
			sprintf_s(caption2, u8"HOME						%d / %d", activeLineIndexCrossCountry + 1, lineCount);
			about = true;//启用独有约束色
			draw_menu_line(caption2, lineWidth, 2.0, 70.0, 25.0, 5.0, false, false);
			about = false;//关闭独有约束色
			for (int i = 0; i < itemCount; i++)
				if (strlen(CrossCountry[activeLineIndexCrossCountry][i]))
					draw_menu_line(CrossCountry[activeLineIndexCrossCountry][i], 250.0, 5.0, 91. + i * 27.5, 25.0, 5.0, false, false);
			draw_menu_line(line_as_str(CrossCountry[activeLineIndexCrossCountry][activeLineIndexCrossCountryItem], NULL),
				lineWidth, 5.0, 91. + activeLineIndexCrossCountryItem * 27.5, 25.0, 5.0, true, false);
			Bottom = true;
			draw_menu_line(u8"1.58   	   NEVERLOSE 免费		0.2.1", lineWidth, 5.0, 285.5, 25.0, 5.0, false, false);
			Bottom = false;
			update_features();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;

		bool bSelect, bBack, bUp, bDown, bLeft, bRight;
		get_button_state(&bSelect, &bBack, &bUp, &bDown, &bLeft, &bRight);

		if (bSelect)
		{
			menu_beep();
			LPCSTR modelName = CrossCountry[activeLineIndexCrossCountry][activeLineIndexCrossCountryItem];
			DWORD model = GAMEPLAY::GET_HASH_KEY((char*)modelName);
			if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_A_VEHICLE(model))
			{
				STREAMING::REQUEST_MODEL(model);
				while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(0);
				Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0, 5.0, 0.0);
				Vehicle veh = VEHICLE::CREATE_VEHICLE(model, coords.x, coords.y, coords.z, 0.0, 1, 1);
				VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);

				if (featureVenaircraft)
				{
					ENTITY::SET_ENTITY_HEADING(veh, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
					PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
				}

				WAIT(0);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
				ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&veh);

				char statusText[32];
				sprintf_s(statusText, "%s spawned", modelName);
				set_status_text(statusText);

				return true;
			}
		}
		else
			if (bBack)
			{
				menu_beep();
				break;
			}
			else
				if (bRight)
				{
					//右

					menu_beep();
					activeLineIndexCrossCountry++;
					if (activeLineIndexCrossCountry == lineCount)
						activeLineIndexCrossCountry = 0;
					waitTime = 200;
				}
				else
					if (bLeft)
					{
						//左

						menu_beep();
						if (activeLineIndexCrossCountry == 0)
							activeLineIndexCrossCountry = lineCount;
						activeLineIndexCrossCountry--;
						waitTime = 200;
					}
					else
						if (bUp)
						{
							//上
							menu_beep();
							if (activeLineIndexCrossCountryItem == 0)
								activeLineIndexCrossCountryItem = (activeLineIndexCrossCountry == (lineCount - 1)) ? itemCountLastLine : itemCount;
							activeLineIndexCrossCountryItem--;
							waitTime = 100;
						}
						else
							if (bDown)
							{
								//下
								menu_beep();
								activeLineIndexCrossCountryItem++;
								int itemsMax = (activeLineIndexCrossCountry == (lineCount - 1)) ? itemCountLastLine : itemCount;
								if (activeLineIndexCrossCountryItem == itemsMax)
									activeLineIndexCrossCountryItem = 0;
								waitTime = 100;
							}
		if (activeLineIndexCrossCountry == (lineCount - 1))
			if (activeLineIndexCrossCountryItem >= itemCountLastLine)
				activeLineIndexCrossCountryItem = 0;
	}
	return false;
}


int activeLineIndexSportsSUVS = 0;
int activeLineIndexSportsSUVSItem = 0;

LPCSTR SportsSUVS[2][10] = {
	{"CAVALCADE","CAVALCADE2","DUBSTA","DUBSTA2","SERRANO","GRESLEY","MESA","MESA2","SEMINOLE","GRANGER"},
	{"LANDSTALKER","HABANERO","HUNTLEY","FQ2","BALLER","BALLER2","BJXL","PATRIOT","ROCOTO","RADI"}
};

bool process_SportsSUVS_Vehicle_menu() {
	DWORD waitTime = 150;
	const int lineCount = 2;
	const int itemCount = 10;
	const int itemCountLastLine = 10;
	const float lineWidth = 250.0;

	while (true)
	{

		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			// draw menu
			draw_menu_line(u8"运动休旅车 SUVS", lineWidth, 15.0, 15.0, 25.0, 55.0, false, true);
			char caption2[32];
			sprintf_s(caption2, u8"HOME						%d / %d", activeLineIndexSportsSUVS + 1, lineCount);
			about = true;//启用独有约束色
			draw_menu_line(caption2, lineWidth, 2.0, 70.0, 25.0, 5.0, false, false);
			about = false;//关闭独有约束色
			for (int i = 0; i < itemCount; i++)
				if (strlen(SportsSUVS[activeLineIndexSportsSUVS][i]))
					draw_menu_line(SportsSUVS[activeLineIndexSportsSUVS][i], 250.0, 5.0, 91. + i * 27.5, 25.0, 5.0, false, false);
			draw_menu_line(line_as_str(SportsSUVS[activeLineIndexSportsSUVS][activeLineIndexSportsSUVSItem], NULL),
				lineWidth, 5.0, 91. + activeLineIndexSportsSUVSItem * 27.5, 25.0, 5.0, true, false);
			Bottom = true;
			draw_menu_line(u8"1.58   	   NEVERLOSE 免费		0.2.1", lineWidth, 5.0, 368.5, 25.0, 5.0, false, false);
			Bottom = false;
			update_features();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;

		bool bSelect, bBack, bUp, bDown, bLeft, bRight;
		get_button_state(&bSelect, &bBack, &bUp, &bDown, &bLeft, &bRight);

		if (bSelect)
		{
			menu_beep();
			LPCSTR modelName = SportsSUVS[activeLineIndexSportsSUVS][activeLineIndexSportsSUVSItem];
			DWORD model = GAMEPLAY::GET_HASH_KEY((char*)modelName);
			if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_A_VEHICLE(model))
			{
				STREAMING::REQUEST_MODEL(model);
				while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(0);
				Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0, 5.0, 0.0);
				Vehicle veh = VEHICLE::CREATE_VEHICLE(model, coords.x, coords.y, coords.z, 0.0, 1, 1);
				VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);

				if (featureVenaircraft)
				{
					ENTITY::SET_ENTITY_HEADING(veh, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
					PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
				}

				WAIT(0);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
				ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&veh);

				char statusText[32];
				sprintf_s(statusText, "%s spawned", modelName);
				set_status_text(statusText);

				return true;
			}
		}
		else
			if (bBack)
			{
				menu_beep();
				break;
			}
			else
				if (bRight)
				{
					//右

					menu_beep();
					activeLineIndexSportsSUVS++;
					if (activeLineIndexSportsSUVS == lineCount)
						activeLineIndexSportsSUVS = 0;
					waitTime = 200;
				}
				else
					if (bLeft)
					{
						//左

						menu_beep();
						if (activeLineIndexSportsSUVS == 0)
							activeLineIndexSportsSUVS = lineCount;
						activeLineIndexSportsSUVS--;
						waitTime = 200;
					}
					else
						if (bUp)
						{
							//上
							menu_beep();
							if (activeLineIndexSportsSUVSItem == 0)
								activeLineIndexSportsSUVSItem = (activeLineIndexSportsSUVS == (lineCount - 1)) ? itemCountLastLine : itemCount;
							activeLineIndexSportsSUVSItem--;
							waitTime = 100;
						}
						else
							if (bDown)
							{
								//下
								menu_beep();
								activeLineIndexSportsSUVSItem++;
								int itemsMax = (activeLineIndexSportsSUVS == (lineCount - 1)) ? itemCountLastLine : itemCount;
								if (activeLineIndexSportsSUVSItem == itemsMax)
									activeLineIndexSportsSUVSItem = 0;
								waitTime = 100;
							}
		if (activeLineIndexSportsSUVS == (lineCount - 1))
			if (activeLineIndexSportsSUVSItem >= itemCountLastLine)
				activeLineIndexSportsSUVSItem = 0;
	}
	return false;
}

int activeLineIndexCar = 0;
int activeLineIndexCarItem = 0;

LPCSTR CarVehicle[5][5] = {
	{"EMPEROR","EMPEROR2","EMPEROR3","PRIMO","STRETCH"},
	{"WASHINGTON","GLENDALE","SCHAFTER2","ROMERO","FUGITIVE"},
	{"SURGE","ASEA","ASEA2","PREMIER","REGINA"},
	{"SUPERD","ASTEROPE","INTRUDER","TAILGATER","ORACLE"},
	{"ORACLE2","STANIER","TAXI","INGOT","WARRENER"}
};

bool process_Car_menu() {

	DWORD waitTime = 150;
	const int lineCount = 5;
	const int itemCount = 5;
	const int itemCountLastLine = 5;
	const float lineWidth = 250.0;

	while (true)
	{

		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			// draw menu
			draw_menu_line(u8"轿车", lineWidth, 15.0, 15.0, 25.0, 105.0, false, true);
			char caption2[32];
			sprintf_s(caption2, u8"HOME						%d / %d", activeLineIndexCar + 1, lineCount);
			about = true;//启用独有约束色
			draw_menu_line(caption2, lineWidth, 2.0, 70.0, 25.0, 5.0, false, false);
			about = false;//关闭独有约束色
			for (int i = 0; i < itemCount; i++)
				if (strlen(CarVehicle[activeLineIndexCar][i]))
					draw_menu_line(CarVehicle[activeLineIndexCar][i], 250.0, 5.0, 91. + i * 27.5, 25.0, 5.0, false, false);
			draw_menu_line(line_as_str(CarVehicle[activeLineIndexCar][activeLineIndexCarItem], NULL),
				lineWidth, 5.0, 91. + activeLineIndexCarItem * 27.5, 25.0, 5.0, true, false);
			Bottom = true;
			draw_menu_line(u8"1.58   	   NEVERLOSE 免费		0.2.1", lineWidth, 5.0, 230.0, 25.0, 5.0, false, false);
			Bottom = false;
			update_features();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;

		bool bSelect, bBack, bUp, bDown, bLeft, bRight;
		get_button_state(&bSelect, &bBack, &bUp, &bDown, &bLeft, &bRight);

		if (bSelect)
		{
			menu_beep();
			LPCSTR modelName = CarVehicle[activeLineIndexCar][activeLineIndexCarItem];
			DWORD model = GAMEPLAY::GET_HASH_KEY((char*)modelName);
			if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_A_VEHICLE(model))
			{
				STREAMING::REQUEST_MODEL(model);
				while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(0);
				Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0, 5.0, 0.0);
				Vehicle veh = VEHICLE::CREATE_VEHICLE(model, coords.x, coords.y, coords.z, 0.0, 1, 1);
				VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);

				if (featureVenaircraft)
				{
					ENTITY::SET_ENTITY_HEADING(veh, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
					PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
				}

				WAIT(0);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
				ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&veh);

				char statusText[32];
				sprintf_s(statusText, "%s spawned", modelName);
				set_status_text(statusText);

				return true;
			}
		}
		else
			if (bBack)
			{
				menu_beep();
				break;
			}
			else
				if (bRight)
				{
					//右

					menu_beep();
					activeLineIndexCar++;
					if (activeLineIndexCar == lineCount)
						activeLineIndexCar = 0;
					waitTime = 200;
				}
				else
					if (bLeft)
					{
						//左

						menu_beep();
						if (activeLineIndexCar == 0)
							activeLineIndexCar = lineCount;
						activeLineIndexCar--;
						waitTime = 200;
					}
					else
						if (bUp)
						{
							//上
							menu_beep();
							if (activeLineIndexCarItem == 0)
								activeLineIndexCarItem = (activeLineIndexCar == (lineCount - 1)) ? itemCountLastLine : itemCount;
							activeLineIndexCarItem--;
							waitTime = 100;
						}
						else
							if (bDown)
							{
								//下
								menu_beep();
								activeLineIndexCarItem++;
								int itemsMax = (activeLineIndexCar == (lineCount - 1)) ? itemCountLastLine : itemCount;
								if (activeLineIndexCarItem == itemsMax)
									activeLineIndexCarItem = 0;
								waitTime = 100;
							}
		if (activeLineIndexCar == (lineCount - 1))
			if (activeLineIndexCarItem >= itemCountLastLine)
				activeLineIndexCarItem = 0;
	}
	return false;
}


int activeLineIndexSmallCar = 0;
int activeLineIndexSmallCarItem = 0;

LPCSTR SmallCar[1][7] = {
	{"PANTO","PRAIRIE","RHAPSODY","BLISTA","DILETTANTE","DILETTANTE2","ISSI2"}
};

bool process_Small_Car_menu() {
	DWORD waitTime = 150;
	const int lineCount = 1;
	const int itemCount = 7;
	const int itemCountLastLine = 7;
	const float lineWidth = 250.0;

	while (true)
	{

		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			// draw menu
			draw_menu_line(u8"小型汽车", lineWidth, 15.0, 15.0, 25.0, 105.0, false, true);
			char caption2[32];
			sprintf_s(caption2, u8"HOME						%d / %d", activeLineIndexSmallCar + 1, lineCount);
			about = true;//启用独有约束色
			draw_menu_line(caption2, lineWidth, 2.0, 70.0, 25.0, 5.0, false, false);
			about = false;//关闭独有约束色
			for (int i = 0; i < itemCount; i++)
				if (strlen(SmallCar[activeLineIndexSmallCar][i]))
					draw_menu_line(SmallCar[activeLineIndexSmallCar][i], 250.0, 5.0, 91. + i * 27.5, 25.0, 5.0, false, false);
			draw_menu_line(line_as_str(SmallCar[activeLineIndexSmallCar][activeLineIndexSmallCarItem], NULL),
				lineWidth, 5.0, 91. + activeLineIndexSmallCarItem * 27.5, 25.0, 5.0, true, false);
			Bottom = true;
			draw_menu_line(u8"1.58   	   NEVERLOSE 免费		0.2.1", lineWidth, 5.0, 285.5, 25.0, 5.0, false, false);
			Bottom = false;
			update_features();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;

		bool bSelect, bBack, bUp, bDown, bLeft, bRight;
		get_button_state(&bSelect, &bBack, &bUp, &bDown, &bLeft, &bRight);

		if (bSelect)
		{
			menu_beep();
			LPCSTR modelName = SmallCar[activeLineIndexSmallCar][activeLineIndexSmallCarItem];
			DWORD model = GAMEPLAY::GET_HASH_KEY((char*)modelName);
			if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_A_VEHICLE(model))
			{
				STREAMING::REQUEST_MODEL(model);
				while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(0);
				Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0, 5.0, 0.0);
				Vehicle veh = VEHICLE::CREATE_VEHICLE(model, coords.x, coords.y, coords.z, 0.0, 1, 1);
				VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);

				if (featureVenaircraft)
				{
					ENTITY::SET_ENTITY_HEADING(veh, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
					PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
				}

				WAIT(0);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
				ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&veh);

				char statusText[32];
				sprintf_s(statusText, "%s spawned", modelName);
				set_status_text(statusText);

				return true;
			}
		}
		else
			if (bBack)
			{
				menu_beep();
				break;
			}
			else
				if (bRight)
				{
					//右

					menu_beep();
					activeLineIndexSmallCar++;
					if (activeLineIndexSmallCar == lineCount)
						activeLineIndexSmallCar = 0;
					waitTime = 200;
				}
				else
					if (bLeft)
					{
						//左

						menu_beep();
						if (activeLineIndexSmallCar == 0)
							activeLineIndexSmallCar = lineCount;
						activeLineIndexSmallCar--;
						waitTime = 200;
					}
					else
						if (bUp)
						{
							//上
							menu_beep();
							if (activeLineIndexSmallCarItem == 0)
								activeLineIndexSmallCarItem = (activeLineIndexSmallCar == (lineCount - 1)) ? itemCountLastLine : itemCount;
							activeLineIndexSmallCarItem--;
							waitTime = 100;
						}
						else
							if (bDown)
							{
								//下
								menu_beep();
								activeLineIndexSmallCarItem++;
								int itemsMax = (activeLineIndexSmallCar == (lineCount - 1)) ? itemCountLastLine : itemCount;
								if (activeLineIndexSmallCarItem == itemsMax)
									activeLineIndexSmallCarItem = 0;
								waitTime = 100;
							}
		if (activeLineIndexSmallCar == (lineCount - 1))
			if (activeLineIndexSmallCarItem >= itemCountLastLine)
				activeLineIndexSmallCarItem = 0;
	}
	return false;
}

int activeLineIndexPickUp = 0;
int activeLineIndexPickUpItem = 0;

LPCSTR PickUp[1][8] = {
	{"BISON","BISON3","BISON2","RATLOADER2","RATLOADER","BOBCATXL","SADLER","SADLER2"}
};

bool process_PickUp_menu() {
	DWORD waitTime = 150;
	const int lineCount = 1;
	const int itemCount = 8;
	const int itemCountLastLine = 8;
	const float lineWidth = 250.0;

	while (true)
	{

		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			// draw menu
			draw_menu_line(u8"皮卡 PICKUPS", lineWidth, 15.0, 15.0, 25.0, 75.0, false, true);
			char caption2[32];
			sprintf_s(caption2, u8"HOME						%d / %d", activeLineIndexPickUp + 1, lineCount);
			about = true;//启用独有约束色
			draw_menu_line(caption2, lineWidth, 2.0, 70.0, 25.0, 5.0, false, false);
			about = false;//关闭独有约束色
			for (int i = 0; i < itemCount; i++)
				if (strlen(PickUp[activeLineIndexPickUp][i]))
					draw_menu_line(PickUp[activeLineIndexPickUp][i], 250.0, 5.0, 91. + i * 27.5, 25.0, 5.0, false, false);
			draw_menu_line(line_as_str(PickUp[activeLineIndexPickUp][activeLineIndexPickUpItem], NULL),
				lineWidth, 5.0, 91. + activeLineIndexPickUpItem * 27.5, 25.0, 5.0, true, false);
			Bottom = true;
			draw_menu_line(u8"1.58   	   NEVERLOSE 免费		0.2.1", lineWidth, 5.0, 313.5, 25.0, 5.0, false, false);
			Bottom = false;
			update_features();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;

		bool bSelect, bBack, bUp, bDown, bLeft, bRight;
		get_button_state(&bSelect, &bBack, &bUp, &bDown, &bLeft, &bRight);

		if (bSelect)
		{
			menu_beep();
			LPCSTR modelName = PickUp[activeLineIndexPickUp][activeLineIndexPickUpItem];
			DWORD model = GAMEPLAY::GET_HASH_KEY((char*)modelName);
			if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_A_VEHICLE(model))
			{
				STREAMING::REQUEST_MODEL(model);
				while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(0);
				Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0, 5.0, 0.0);
				Vehicle veh = VEHICLE::CREATE_VEHICLE(model, coords.x, coords.y, coords.z, 0.0, 1, 1);
				VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);

				if (featureVenaircraft)
				{
					ENTITY::SET_ENTITY_HEADING(veh, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
					PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
				}

				WAIT(0);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
				ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&veh);

				char statusText[32];
				sprintf_s(statusText, "%s spawned", modelName);
				set_status_text(statusText);

				return true;
			}
		}
		else
			if (bBack)
			{
				menu_beep();
				break;
			}
			else
				if (bRight)
				{
					//右

					menu_beep();
					activeLineIndexPickUp++;
					if (activeLineIndexPickUp == lineCount)
						activeLineIndexPickUp = 0;
					waitTime = 200;
				}
				else
					if (bLeft)
					{
						//左

						menu_beep();
						if (activeLineIndexPickUp == 0)
							activeLineIndexPickUp = lineCount;
						activeLineIndexPickUp--;
						waitTime = 200;
					}
					else
						if (bUp)
						{
							//上
							menu_beep();
							if (activeLineIndexPickUpItem == 0)
								activeLineIndexPickUpItem = (activeLineIndexPickUp == (lineCount - 1)) ? itemCountLastLine : itemCount;
							activeLineIndexPickUpItem--;
							waitTime = 100;
						}
						else
							if (bDown)
							{
								//下
								menu_beep();
								activeLineIndexPickUpItem++;
								int itemsMax = (activeLineIndexPickUp == (lineCount - 1)) ? itemCountLastLine : itemCount;
								if (activeLineIndexPickUpItem == itemsMax)
									activeLineIndexPickUpItem = 0;
								waitTime = 100;
							}
		if (activeLineIndexPickUp == (lineCount - 1))
			if (activeLineIndexPickUpItem >= itemCountLastLine)
				activeLineIndexPickUpItem = 0;
	}
	return false;
}

int activeLineIndexBoxCar = 0;
int activeLineIndexBoxCarItem = 0;

LPCSTR BoxCar[3][7] = {
	{"SURFER","SURFER2","PARADISE","RUMPO2","RUMPO","YOUGA","CAMPER"},
	{"PONY","PONY2","TACO","BURRITO3","BURRITO2","BURRITO4","GBURRITO2"},
	{"BURRITO","BURRITO5","GBURRITO","MINIVAN","SPEEDO","SPEEDO2","JOURNEY"}
};

bool process_Box_Car_menu() {
	DWORD waitTime = 150;
	const int lineCount = 3;
	const int itemCount = 7;
	const int itemCountLastLine = 7;
	const float lineWidth = 250.0;

	while (true)
	{

		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			// draw menu
			draw_menu_line(u8"厢型车 VANS", lineWidth, 15.0, 15.0, 25.0, 105.0, false, true);
			char caption2[32];
			sprintf_s(caption2, u8"HOME						%d / %d", activeLineIndexBoxCar + 1, lineCount);
			about = true;//启用独有约束色
			draw_menu_line(caption2, lineWidth, 2.0, 70.0, 25.0, 5.0, false, false);
			about = false;//关闭独有约束色
			for (int i = 0; i < itemCount; i++)
				if (strlen(BoxCar[activeLineIndexBoxCar][i]))
					draw_menu_line(BoxCar[activeLineIndexBoxCar][i], 250.0, 5.0, 91. + i * 27.5, 25.0, 5.0, false, false);
			draw_menu_line(line_as_str(BoxCar[activeLineIndexBoxCar][activeLineIndexBoxCarItem], NULL),
				lineWidth, 5.0, 91. + activeLineIndexBoxCarItem * 27.5, 25.0, 5.0, true, false);
			Bottom = true;
			draw_menu_line(u8"1.58   	   NEVERLOSE 免费		0.2.1", lineWidth, 5.0, 285.5, 25.0, 5.0, false, false);
			Bottom = false;
			update_features();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;

		bool bSelect, bBack, bUp, bDown, bLeft, bRight;
		get_button_state(&bSelect, &bBack, &bUp, &bDown, &bLeft, &bRight);

		if (bSelect)
		{
			menu_beep();
			LPCSTR modelName = BoxCar[activeLineIndexBoxCar][activeLineIndexBoxCarItem];
			DWORD model = GAMEPLAY::GET_HASH_KEY((char*)modelName);
			if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_A_VEHICLE(model))
			{
				STREAMING::REQUEST_MODEL(model);
				while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(0);
				Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0, 5.0, 0.0);
				Vehicle veh = VEHICLE::CREATE_VEHICLE(model, coords.x, coords.y, coords.z, 0.0, 1, 1);
				VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);

				if (featureVenaircraft)
				{
					ENTITY::SET_ENTITY_HEADING(veh, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
					PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
				}

				WAIT(0);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
				ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&veh);

				char statusText[32];
				sprintf_s(statusText, "%s spawned", modelName);
				set_status_text(statusText);

				return true;
			}
		}
		else
			if (bBack)
			{
				menu_beep();
				break;
			}
			else
				if (bRight)
				{
					//右

					menu_beep();
					activeLineIndexBoxCar++;
					if (activeLineIndexBoxCar == lineCount)
						activeLineIndexBoxCar = 0;
					waitTime = 200;
				}
				else
					if (bLeft)
					{
						//左

						menu_beep();
						if (activeLineIndexBoxCar == 0)
							activeLineIndexBoxCar = lineCount;
						activeLineIndexBoxCar--;
						waitTime = 200;
					}
					else
						if (bUp)
						{
							//上
							menu_beep();
							if (activeLineIndexBoxCarItem == 0)
								activeLineIndexBoxCarItem = (activeLineIndexBoxCar == (lineCount - 1)) ? itemCountLastLine : itemCount;
							activeLineIndexBoxCarItem--;
							waitTime = 100;
						}
						else
							if (bDown)
							{
								//下
								menu_beep();
								activeLineIndexBoxCarItem++;
								int itemsMax = (activeLineIndexBoxCar == (lineCount - 1)) ? itemCountLastLine : itemCount;
								if (activeLineIndexBoxCarItem == itemsMax)
									activeLineIndexBoxCarItem = 0;
								waitTime = 100;
							}
		if (activeLineIndexBoxCar == (lineCount - 1))
			if (activeLineIndexBoxCarItem >= itemCountLastLine)
				activeLineIndexBoxCarItem = 0;
	}
	return false;
}


int activeLineIndexCommercial = 0;
int activeLineIndexCommercialItem = 0;

LPCSTR Commercial[3][9] = {
	{"BOXVILLE2","BOXVILLE3","BOXVILLE4","BOXVILLE","STOCKADE","STOCKADE3","TIPTRUCK","TIPTRUCK2","CUTTER"},
	{"HANDLER","DOCKTUG","DUMP","BIFF","HAULER","PHANTOM","RUBBLE","MULE","MULE2"},
	{"MULE3","MIXER","MIXER2","FLATBED","PACKER","POUNDER","BENSON","SCRAP","TOWTRUCK"}
};

bool process_Commercial_menu() {
	DWORD waitTime = 150;
	const int lineCount = 3;
	const int itemCount = 9;
	const int itemCountLastLine = 9;
	const float lineWidth = 250.0;

	while (true)
	{

		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			// draw menu
			draw_menu_line(u8"商用、工业车", lineWidth, 15.0, 15.0, 25.0, 80.0, false, true);
			char caption2[32];
			sprintf_s(caption2, u8"HOME						%d / %d", activeLineIndexCommercial + 1, lineCount);
			about = true;//启用独有约束色
			draw_menu_line(caption2, lineWidth, 2.0, 70.0, 25.0, 5.0, false, false);
			about = false;//关闭独有约束色
			for (int i = 0; i < itemCount; i++)
				if (strlen(Commercial[activeLineIndexCommercial][i]))
					draw_menu_line(Commercial[activeLineIndexCommercial][i], 250.0, 5.0, 91. + i * 27.5, 25.0, 5.0, false, false);
			draw_menu_line(line_as_str(Commercial[activeLineIndexCommercial][activeLineIndexCommercialItem], NULL),
				lineWidth, 5.0, 91. + activeLineIndexCommercialItem * 27.5, 25.0, 5.0, true, false);
			Bottom = true;
			draw_menu_line(u8"1.58   	   NEVERLOSE 免费		0.2.1", lineWidth, 5.0, 340.5, 25.0, 5.0, false, false);
			Bottom = false;
			update_features();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;

		bool bSelect, bBack, bUp, bDown, bLeft, bRight;
		get_button_state(&bSelect, &bBack, &bUp, &bDown, &bLeft, &bRight);

		if (bSelect)
		{
			menu_beep();
			LPCSTR modelName = Commercial[activeLineIndexCommercial][activeLineIndexCommercialItem];
			DWORD model = GAMEPLAY::GET_HASH_KEY((char*)modelName);
			if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_A_VEHICLE(model))
			{
				STREAMING::REQUEST_MODEL(model);
				while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(0);
				Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0, 5.0, 0.0);
				Vehicle veh = VEHICLE::CREATE_VEHICLE(model, coords.x, coords.y, coords.z, 0.0, 1, 1);
				VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);

				if (featureVenaircraft)
				{
					ENTITY::SET_ENTITY_HEADING(veh, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
					PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
				}

				WAIT(0);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
				ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&veh);

				char statusText[32];
				sprintf_s(statusText, "%s spawned", modelName);
				set_status_text(statusText);

				return true;
			}
		}
		else
			if (bBack)
			{
				menu_beep();
				break;
			}
			else
				if (bRight)
				{
					//右

					menu_beep();
					activeLineIndexCommercial++;
					if (activeLineIndexCommercial == lineCount)
						activeLineIndexCommercial = 0;
					waitTime = 200;
				}
				else
					if (bLeft)
					{
						//左

						menu_beep();
						if (activeLineIndexCommercial == 0)
							activeLineIndexCommercial = lineCount;
						activeLineIndexCommercial--;
						waitTime = 200;
					}
					else
						if (bUp)
						{
							//上
							menu_beep();
							if (activeLineIndexCommercialItem == 0)
								activeLineIndexCommercialItem = (activeLineIndexCommercial == (lineCount - 1)) ? itemCountLastLine : itemCount;
							activeLineIndexCommercialItem--;
							waitTime = 100;
						}
						else
							if (bDown)
							{
								//下
								menu_beep();
								activeLineIndexCommercialItem++;
								int itemsMax = (activeLineIndexCommercial == (lineCount - 1)) ? itemCountLastLine : itemCount;
								if (activeLineIndexCommercialItem == itemsMax)
									activeLineIndexCommercialItem = 0;
								waitTime = 100;
							}
		if (activeLineIndexCommercial == (lineCount - 1))
			if (activeLineIndexCommercialItem >= itemCountLastLine)
				activeLineIndexCommercialItem = 0;
	}
	return false;
}


int activeLineIndexServiceXClass = 0;
int activeLineIndexServiceXClassItem = 0;

LPCSTR ServiceXClass[3][7] = {
	{"AIRTUG","AIRBUS","BUS","RENTALBUS","TOURBUS","CABLECAR","COACH"},
	{"BULLDOZER","FORKLIFT","TRASH2","TRASH","CADDY2","CADDY","RIPLEY"},
	{"TRACTOR2","TRACTOR3","MOWER","TRACTOR","UTILLITRUCK3","UTILLITRUCK2","UTILLITRUCK"}
};

bool process_ServiceXClass_menu() {
	DWORD waitTime = 150;
	const int lineCount = 3;
	const int itemCount = 7;
	const int itemCountLastLine = 7;
	const float lineWidth = 250.0;

	while (true)
	{

		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			// draw menu
			draw_menu_line(u8"服务类", lineWidth, 15.0, 15.0, 25.0, 105.0, false, true);
			char caption2[32];
			sprintf_s(caption2, u8"HOME						%d / %d", activeLineIndexServiceXClass + 1, lineCount);
			about = true;//启用独有约束色
			draw_menu_line(caption2, lineWidth, 2.0, 70.0, 25.0, 5.0, false, false);
			about = false;//关闭独有约束色
			for (int i = 0; i < itemCount; i++)
				if (strlen(ServiceXClass[activeLineIndexServiceXClass][i]))
					draw_menu_line(ServiceXClass[activeLineIndexServiceXClass][i], 250.0, 5.0, 91. + i * 27.5, 25.0, 5.0, false, false);
			draw_menu_line(line_as_str(ServiceXClass[activeLineIndexServiceXClass][activeLineIndexServiceXClassItem], NULL),
				lineWidth, 5.0, 91. + activeLineIndexServiceXClassItem * 27.5, 25.0, 5.0, true, false);
			Bottom = true;
			draw_menu_line(u8"1.58   	   NEVERLOSE 免费		0.2.1", lineWidth, 5.0, 285.5, 25.0, 5.0, false, false);
			Bottom = false;
			update_features();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;

		bool bSelect, bBack, bUp, bDown, bLeft, bRight;
		get_button_state(&bSelect, &bBack, &bUp, &bDown, &bLeft, &bRight);

		if (bSelect)
		{
			menu_beep();
			LPCSTR modelName = ServiceXClass[activeLineIndexServiceXClass][activeLineIndexServiceXClassItem];
			DWORD model = GAMEPLAY::GET_HASH_KEY((char*)modelName);
			if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_A_VEHICLE(model))
			{
				STREAMING::REQUEST_MODEL(model);
				while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(0);
				Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0, 5.0, 0.0);
				Vehicle veh = VEHICLE::CREATE_VEHICLE(model, coords.x, coords.y, coords.z, 0.0, 1, 1);
				VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);

				if (featureVenaircraft)
				{
					ENTITY::SET_ENTITY_HEADING(veh, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
					PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
				}

				WAIT(0);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
				ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&veh);

				char statusText[32];
				sprintf_s(statusText, "%s spawned", modelName);
				set_status_text(statusText);

				return true;
			}
		}
		else
			if (bBack)
			{
				menu_beep();
				break;
			}
			else
				if (bRight)
				{
					//右

					menu_beep();
					activeLineIndexServiceXClass++;
					if (activeLineIndexServiceXClass == lineCount)
						activeLineIndexServiceXClass = 0;
					waitTime = 200;
				}
				else
					if (bLeft)
					{
						//左

						menu_beep();
						if (activeLineIndexServiceXClass == 0)
							activeLineIndexServiceXClass = lineCount;
						activeLineIndexServiceXClass--;
						waitTime = 200;
					}
					else
						if (bUp)
						{
							//上
							menu_beep();
							if (activeLineIndexServiceXClassItem == 0)
								activeLineIndexServiceXClassItem = (activeLineIndexServiceXClass == (lineCount - 1)) ? itemCountLastLine : itemCount;
							activeLineIndexServiceXClassItem--;
							waitTime = 100;
						}
						else
							if (bDown)
							{
								//下
								menu_beep();
								activeLineIndexServiceXClassItem++;
								int itemsMax = (activeLineIndexServiceXClass == (lineCount - 1)) ? itemCountLastLine : itemCount;
								if (activeLineIndexServiceXClassItem == itemsMax)
									activeLineIndexServiceXClassItem = 0;
								waitTime = 100;
							}
		if (activeLineIndexServiceXClass == (lineCount - 1))
			if (activeLineIndexServiceXClassItem >= itemCountLastLine)
				activeLineIndexServiceXClassItem = 0;
	}
	return false;
}

int activeLineIndexTrailer = 0;
int activeLineIndexTrailderItem = 0;

LPCSTR Trailer[2][12] = {
	{"ARMYTRAILER","ARMYTRAILER2","ARMYTANKER","BOATTRAILER","TR3","TR4","TR2","TRAILERS2","TRAILERS3","DOCKTRAILER","TVTRAILER","FREIGHTTRAILER"},
	{"TRFLAT","GRAINTRAILER","BALETRAILER","TRAILERLOGS","PROPTRAILER","TANKER2","TANKER","TRAILERS","RAKETRAILER","TRAILERSMALL","trailerlarge","trailers4"}
};

bool process_Trailer_menu() {
	DWORD waitTime = 150;
	const int lineCount = 2;
	const int itemCount = 12;
	const int itemCountLastLine = 12;
	const float lineWidth = 250.0;

	while (true)
	{

		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			// draw menu
			draw_menu_line(u8"拖车", lineWidth, 15.0, 15.0, 25.0, 105.0, false, true);
			char caption2[32];
			sprintf_s(caption2, u8"HOME						%d / %d", activeLineIndexTrailer + 1, lineCount);
			about = true;//启用独有约束色
			draw_menu_line(caption2, lineWidth, 2.0, 70.0, 25.0, 5.0, false, false);
			about = false;//关闭独有约束色
			for (int i = 0; i < itemCount; i++)
				if (strlen(Trailer[activeLineIndexTrailer][i]))
					draw_menu_line(Trailer[activeLineIndexTrailer][i], 250.0, 5.0, 91. + i * 27.5, 25.0, 5.0, false, false);
			draw_menu_line(line_as_str(Trailer[activeLineIndexTrailer][activeLineIndexTrailderItem], NULL),
				lineWidth, 5.0, 91. + activeLineIndexTrailderItem * 27.5, 25.0, 5.0, true, false);
			Bottom = true;
			draw_menu_line(u8"1.58   	   NEVERLOSE 免费		0.2.1", lineWidth, 5.0, 422.5, 25.0, 5.0, false, false);
			Bottom = false;
			update_features();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;

		bool bSelect, bBack, bUp, bDown, bLeft, bRight;
		get_button_state(&bSelect, &bBack, &bUp, &bDown, &bLeft, &bRight);

		if (bSelect)
		{
			menu_beep();
			LPCSTR modelName = Trailer[activeLineIndexTrailer][activeLineIndexTrailderItem];
			DWORD model = GAMEPLAY::GET_HASH_KEY((char*)modelName);
			if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_A_VEHICLE(model))
			{
				STREAMING::REQUEST_MODEL(model);
				while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(0);
				Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0, 5.0, 0.0);
				Vehicle veh = VEHICLE::CREATE_VEHICLE(model, coords.x, coords.y, coords.z, 0.0, 1, 1);
				VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);

				if (featureVenaircraft)
				{
					ENTITY::SET_ENTITY_HEADING(veh, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
					PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
				}

				WAIT(0);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
				ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&veh);

				char statusText[32];
				sprintf_s(statusText, "%s spawned", modelName);
				set_status_text(statusText);

				return true;
			}
		}
		else
			if (bBack)
			{
				menu_beep();
				break;
			}
			else
				if (bRight)
				{
					//右

					menu_beep();
					activeLineIndexTrailer++;
					if (activeLineIndexTrailer == lineCount)
						activeLineIndexTrailer = 0;
					waitTime = 200;
				}
				else
					if (bLeft)
					{
						//左

						menu_beep();
						if (activeLineIndexTrailer == 0)
							activeLineIndexTrailer = lineCount;
						activeLineIndexTrailer--;
						waitTime = 200;
					}
					else
						if (bUp)
						{
							//上
							menu_beep();
							if (activeLineIndexTrailderItem == 0)
								activeLineIndexTrailderItem = (activeLineIndexTrailer == (lineCount - 1)) ? itemCountLastLine : itemCount;
							activeLineIndexTrailderItem--;
							waitTime = 100;
						}
						else
							if (bDown)
							{
								//下
								menu_beep();
								activeLineIndexTrailderItem++;
								int itemsMax = (activeLineIndexTrailer == (lineCount - 1)) ? itemCountLastLine : itemCount;
								if (activeLineIndexTrailderItem == itemsMax)
									activeLineIndexTrailderItem = 0;
								waitTime = 100;
							}
		if (activeLineIndexTrailer == (lineCount - 1))
			if (activeLineIndexTrailderItem >= itemCountLastLine)
				activeLineIndexTrailderItem = 0;
	}
	return false;
}

int activeLineIndexEmergencyVehicle = 0;
int activeLineIndexEmergencyVehicleItem = 0;


LPCSTR EmergencyVehicle[2][11] = {
	{"POLICEOLD2","AMBULANCE","BARRACKS","BARRACKS2","FBI","RIOT","CRUSADER","FBI2","LGUARD","PRANGER","POLICEOLD1"},
	{"POLICET","SHERIFF2","FIRETRUK","PBUS","RHINO","POLICE2","POLICE","POLICE3","SHERIFF","POLICE4","POLICEB"}
};

bool process_Emergency_Vehicle_menu() {
	DWORD waitTime = 150;
	const int lineCount = 2;
	const int itemCount = 11;
	const int itemCountLastLine = 11;
	const float lineWidth = 250.0;

	while (true)
	{

		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			// draw menu
			draw_menu_line(u8"紧急车辆", lineWidth, 15.0, 15.0, 25.0, 105.0, false, true);
			char caption2[32];
			sprintf_s(caption2, u8"HOME						%d / %d", activeLineIndexEmergencyVehicle + 1, lineCount);
			about = true;//启用独有约束色
			draw_menu_line(caption2, lineWidth, 2.0, 70.0, 25.0, 5.0, false, false);
			about = false;//关闭独有约束色
			for (int i = 0; i < itemCount; i++)
				if (strlen(EmergencyVehicle[activeLineIndexEmergencyVehicle][i]))
					draw_menu_line(EmergencyVehicle[activeLineIndexEmergencyVehicle][i], 250.0, 5.0, 91. + i * 27.5, 25.0, 5.0, false, false);
			draw_menu_line(line_as_str(EmergencyVehicle[activeLineIndexEmergencyVehicle][activeLineIndexEmergencyVehicleItem], NULL),
				lineWidth, 5.0, 91. + activeLineIndexEmergencyVehicleItem * 27.5, 25.0, 5.0, true, false);
			Bottom = true;
			draw_menu_line(u8"1.58   	   NEVERLOSE 免费		0.2.1", lineWidth, 5.0, 395.5, 25.0, 5.0, false, false);
			Bottom = false;
			update_features();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;

		bool bSelect, bBack, bUp, bDown, bLeft, bRight;
		get_button_state(&bSelect, &bBack, &bUp, &bDown, &bLeft, &bRight);

		if (bSelect)
		{
			menu_beep();
			LPCSTR modelName = EmergencyVehicle[activeLineIndexEmergencyVehicle][activeLineIndexEmergencyVehicleItem];
			DWORD model = GAMEPLAY::GET_HASH_KEY((char*)modelName);
			if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_A_VEHICLE(model))
			{
				STREAMING::REQUEST_MODEL(model);
				while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(0);
				Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0, 5.0, 0.0);
				Vehicle veh = VEHICLE::CREATE_VEHICLE(model, coords.x, coords.y, coords.z, 0.0, 1, 1);
				VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);

				if (featureVenaircraft)
				{
					ENTITY::SET_ENTITY_HEADING(veh, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
					PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
				}

				WAIT(0);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
				ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&veh);

				char statusText[32];
				sprintf_s(statusText, "%s spawned", modelName);
				set_status_text(statusText);

				return true;
			}
		}
		else
			if (bBack)
			{
				menu_beep();
				break;
			}
			else
				if (bRight)
				{
					//右

					menu_beep();
					activeLineIndexEmergencyVehicle++;
					if (activeLineIndexEmergencyVehicle == lineCount)
						activeLineIndexEmergencyVehicle = 0;
					waitTime = 200;
				}
				else
					if (bLeft)
					{
						//左

						menu_beep();
						if (activeLineIndexEmergencyVehicle == 0)
							activeLineIndexEmergencyVehicle = lineCount;
						activeLineIndexEmergencyVehicle--;
						waitTime = 200;
					}
					else
						if (bUp)
						{
							//上
							menu_beep();
							if (activeLineIndexEmergencyVehicleItem == 0)
								activeLineIndexEmergencyVehicleItem = (activeLineIndexEmergencyVehicle == (lineCount - 1)) ? itemCountLastLine : itemCount;
							activeLineIndexEmergencyVehicleItem--;
							waitTime = 100;
						}
						else
							if (bDown)
							{
								//下
								menu_beep();
								activeLineIndexEmergencyVehicleItem++;
								int itemsMax = (activeLineIndexEmergencyVehicle == (lineCount - 1)) ? itemCountLastLine : itemCount;
								if (activeLineIndexEmergencyVehicleItem == itemsMax)
									activeLineIndexEmergencyVehicleItem = 0;
								waitTime = 100;
							}
		if (activeLineIndexEmergencyVehicle == (lineCount - 1))
			if (activeLineIndexEmergencyVehicleItem >= itemCountLastLine)
				activeLineIndexEmergencyVehicleItem = 0;
	}
	return false;
}




int activeLineIndexTrain = 0;

void process_train_menu() {
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(u8"火车菜单已打开");
	// 提示声音
	PlayFrontend("Phone_SoundSet_Default", "Text_Arrive_Tone");

	UI::_DRAW_NOTIFICATION(0, 0);


	const float lineWidth = 250.0;
	const int lineCount = 7;

	std::string caption = u8"火车";
	static struct {
		LPCSTR		text;
		bool* pState;
		bool* pUpdated;
	} lines[lineCount] = {
			{u8"火车集装箱 1					  ", NULL, NULL},
			{u8"火车集装箱 2					  ", NULL, NULL},
			{u8"火车车托						  ", NULL, NULL},
			{u8"火车车头						  ", NULL, NULL},
			{u8"火车货柜						  ", NULL, NULL},
			{u8"电车 (一半)					  ", NULL, NULL},
			{u8"油罐							  ", NULL, NULL}

	};

	DWORD waitTime = 150;
	while (true)
	{
		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			draw_menu_line(caption, lineWidth, 15.0, 15.0, 25.0, 105.0, false, true);
			char caption2[32];
			sprintf_s(caption2, u8"HOME					   %d / %d", activeLineIndexTrain + 1, lineCount);
			about = true;//启用独有约束色
			draw_menu_line(caption2, lineWidth, 2.0, 70.0, 25.0, 5.0, false, false);
			about = false;//关闭独有约束色
			for (int i = 0; i < lineCount; i++)
				if (i != activeLineIndexTrain)
					draw_menu_line(line_as_str(lines[i].text, lines[i].pState),
						lineWidth, 5.0, 91. + i * 27.5, 25.0, 9.0, false, false);
			draw_menu_line(line_as_str(lines[activeLineIndexTrain].text, lines[activeLineIndexTrain].pState),
				lineWidth, 5.0, 91. + activeLineIndexTrain * 27.5, 25.0, 9.0, true, false);
			Bottom = true;
			draw_menu_line(u8"1.58   	   NEVERLOSE 免费		0.2.1", lineWidth, 5.0, 285.5, 25.0, 5.0, false, false);
			Bottom = false;
			update_features();
			WAIT(0);

		} while (GetTickCount() < maxTickCount);
		waitTime = 0;
		bool bSelect, bBack, bUp, bDown;
		get_button_state(&bSelect, &bBack, &bUp, &bDown, NULL, NULL);
		if (bSelect)
		{
			menu_beep();
			switch (activeLineIndexTrain)
			{
			case 0:; break;
			case 1:; break;
			case 2:; break;
			case 3:; break;
			case 4:; break;
			case 5:; break;
			case 6:; break;

			}
			waitTime = 200;
		}
		else
			if (bBack || trainer_switch_pressed())
			{
				menu_beep();
				break;
			}
			else
				if (bUp)
				{
					menu_beep();
					if (activeLineIndexTrain == 0)
						activeLineIndexTrain = lineCount;
					activeLineIndexTrain--;
					waitTime = 150;
				}
				else
					if (bDown)
					{
						menu_beep();
						activeLineIndexTrain++;
						if (activeLineIndexTrain == lineCount)
							activeLineIndexTrain = 0;
						waitTime = 150;
					}
	}
}


int activeLineIndexStandardcar = 0;

void process_Standardcar_menu() {
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(u8"经典汽车菜单已打开");
	// 提示声音
	PlayFrontend("Phone_SoundSet_Default", "Text_Arrive_Tone");

	UI::_DRAW_NOTIFICATION(0, 0);

	const float lineWidth = 250.0;
	const int lineCount = 15;

	std::string caption = u8"经典汽车";
	static struct {
		LPCSTR		text;
		bool* pState;
		bool* pUpdated;
	} lines[lineCount] = {
			{u8"超级跑车						  >", NULL, NULL},
			{u8"跑车							  >", NULL, NULL},
			{u8"经典跑车						  >", NULL, NULL},
			{u8"轿跑车						  >", NULL, NULL},
			{u8"肌肉车						  >", NULL, NULL},
			{u8"越野车						  >", NULL, NULL},
			{u8"运动休旅车 SUVS				  >", NULL, NULL},
			{u8"轿车							  >", NULL, NULL},
			{u8"小型汽车						  >", NULL, NULL},
			{u8"皮卡 PICKUPS					  >", NULL, NULL},
			{u8"厢型车 VANS					  >", NULL, NULL},
			{u8"商用、工业车					  >", NULL, NULL},
			{u8"服务类						  >", NULL, NULL},
			{u8"拖车							  >", NULL, NULL},
			{u8"紧急车辆						  >", NULL, NULL}
	};
	DWORD waitTime = 150;
	while (true)
	{
		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			draw_menu_line(caption, lineWidth, 15.0, 15.0, 25.0, 105.0, false, true);
			char caption2[32];
			sprintf_s(caption2, u8"HOME					   %d / %d", activeLineIndexStandardcar + 1, lineCount);
			about = true;//启用独有约束色
			draw_menu_line(caption2, lineWidth, 2.0, 70.0, 25.0, 5.0, false, false);
			about = false;//关闭独有约束色
			for (int i = 0; i < lineCount; i++)
				if (i != activeLineIndexStandardcar)
					draw_menu_line(line_as_str(lines[i].text, lines[i].pState),
						lineWidth, 5.0, 91. + i * 27.5, 25.0, 9.0, false, false);
			draw_menu_line(line_as_str(lines[activeLineIndexStandardcar].text, lines[activeLineIndexStandardcar].pState),
				lineWidth, 5.0, 91. + activeLineIndexStandardcar * 27.5, 25.0, 9.0, true, false);
			Bottom = true;
			draw_menu_line(u8"1.58   	   NEVERLOSE 免费		0.2.1", lineWidth, 5.0, 505.5, 25.0, 5.0, false, false);
			Bottom = false;
			update_features();
			WAIT(0);

		} while (GetTickCount() < maxTickCount);
		waitTime = 0;
		bool bSelect, bBack, bUp, bDown;
		get_button_state(&bSelect, &bBack, &bUp, &bDown, NULL, NULL);
		if (bSelect)
		{
			menu_beep();
			switch (activeLineIndexStandardcar)
			{
			case 0:process_SuperCar_menu(); break;
			case 1:process_SportsCar_menu(); break;
			case 2:process_jindianSportsCar_menu(); break;
			case 3:process_Coupe_menu(); break;
			case 4:process_Muscle_menu(); break;
			case 5:process_CrossCountry_menu(); break;
			case 6:process_SportsSUVS_Vehicle_menu(); break;
			case 7:process_Car_menu(); break;
			case 8:process_Small_Car_menu(); break;
			case 9:process_PickUp_menu(); break;
			case 10:process_Box_Car_menu(); break;
			case 11:process_Commercial_menu(); break;
			case 12:process_ServiceXClass_menu(); break;
			case 13:process_Trailer_menu(); break;
			case 14:process_Emergency_Vehicle_menu(); break;
			}
			waitTime = 200;
		}
		else
			if (bBack || trainer_switch_pressed())
			{
				menu_beep();
				break;
			}
			else
				if (bUp)
				{
					menu_beep();
					if (activeLineIndexStandardcar == 0)
						activeLineIndexStandardcar = lineCount;
					activeLineIndexStandardcar--;
					waitTime = 150;
				}
				else
					if (bDown)
					{
						menu_beep();
						activeLineIndexStandardcar++;
						if (activeLineIndexStandardcar == lineCount)
							activeLineIndexStandardcar = 0;
						waitTime = 150;
					}
	}

}












int activeLineIndexPlayer = 0;

void process_player_menu()
{
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(u8"玩家选项已打开");
	// 提示声音
	PlayFrontend("Phone_SoundSet_Default", "Text_Arrive_Tone");

	UI::_DRAW_NOTIFICATION(0, 0);
	const float lineWidth = 250.0;
	const int lineCount = 15;

	std::string caption = u8"玩家选项";

	static struct {
		LPCSTR		text;
		bool* pState;
		bool* pUpdated;
	} lines[lineCount] = {
		{u8"换肤器", NULL, NULL},
		{u8"传送", NULL, NULL},
		{u8"修理工", NULL, NULL},
		{u8"重置皮肤", NULL, NULL},
		{u8"加现金", NULL, NULL},
		{u8"通缉", NULL, NULL},
		{u8"想打倒", NULL, NULL},
		{u8"从没想过					   ", &featurePlayerNeverWanted, NULL},
		{u8"无敌的				           ", &featurePlayerInvincible, &featurePlayerInvincibleUpdated},
		{u8"警方不予理睬				   ", &featurePlayerIgnored, &featurePlayerIgnoredUpdated},
		{u8"不发光能力				   ", &featurePlayerUnlimitedAbility, NULL},
		{u8"无声的				           ", &featurePlayerNoNoise, &featurePlayerNoNoiseUpdated},
		{u8"快速游泳					   ", &featurePlayerFastSwim, &featurePlayerFastSwimUpdated},
		{u8"快跑					           ", &featurePlayerFastRun, &featurePlayerFastRunUpdated},
		{u8"超级跳跃					   ", &featurePlayerSuperJump, NULL}
	};

	DWORD waitTime = 150;
	while (true)
	{
		// 菜单绘制，用于激活线路切换后暂停
		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			// 绘图菜单
			draw_menu_line(caption, lineWidth, 15.0, 15.0, 25.0, 75.0, false, true);
			char caption2[32];
			sprintf_s(caption2, u8"HOME					   %d / %d", activeLineIndexPlayer + 1, lineCount);
			about = true;//启用独有约束色
			draw_menu_line(caption2, lineWidth, 2.0, 70.0, 25.0, 5.0, false, false);
			about = false;//关闭独有约束色
			for (int i = 0; i < lineCount; i++)
				if (i != activeLineIndexPlayer)
					draw_menu_line(line_as_str(lines[i].text, lines[i].pState),
						lineWidth, 5.0, 91. + i * 27.5, 25.0, 9.0, false, false);
			draw_menu_line(line_as_str(lines[activeLineIndexPlayer].text, lines[activeLineIndexPlayer].pState),
				lineWidth , 5.0, 91. + activeLineIndexPlayer * 27.5, 25.0, 9.0, true, false);
			Bottom = true;
			draw_menu_line(u8"1.58   	   NEVERLOSE 免费		0.2.1", lineWidth, 5.0, 505.5, 25.0, 5.0, false, false);
			Bottom = false;
			update_features();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;

		// 进程按钮
		bool bSelect, bBack, bUp, bDown;
		get_button_state(&bSelect, &bBack, &bUp, &bDown, NULL, NULL);
		if (bSelect)
		{
			menu_beep();

			// 公共变量
			BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
			Player player = PLAYER::PLAYER_ID();
			Ped playerPed = PLAYER::PLAYER_PED_ID();

			switch (activeLineIndexPlayer)
			{
				// 换肤器
			case 0:
				if (process_skinchanger_menu())	return;
				break;
				// 传送
			case 1:
				if (process_teleport_menu()) return;
				break;
				// 固定播放器
			case 2:
			{
				ENTITY::SET_ENTITY_HEALTH(playerPed, ENTITY::GET_ENTITY_MAX_HEALTH(playerPed));
				PED::ADD_ARMOUR_TO_PED(playerPed, PLAYER::GET_PLAYER_MAX_ARMOUR(player) - PED::GET_PED_ARMOUR(playerPed));
				if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
				{
					Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
					if (ENTITY::DOES_ENTITY_EXIST(playerVeh) && !ENTITY::IS_ENTITY_DEAD(playerVeh))
						VEHICLE::SET_VEHICLE_FIXED(playerVeh);
				}
				set_status_text("player fixed");
			}
			break;
			// 重置模型蒙皮
			case 3:
			{
				PED::SET_PED_DEFAULT_COMPONENT_VARIATION(playerPed);
				set_status_text("using default model skin");
			}
			break;
			// 加现金
			case 4:
				for (int i = 0; i < 3; i++)
				{
					char statNameFull[32];
					sprintf_s(statNameFull, "SP%d_TOTAL_CASH", i);
					Hash hash = GAMEPLAY::GET_HASH_KEY(statNameFull);
					int val;
					STATS::STAT_GET_INT(hash, &val, -1);
					val += 1000000;
					STATS::STAT_SET_INT(hash, val, 1);
				}
				set_status_text("cash added");
				break;
				// 获取警星
			case 5:
				if (bPlayerExists && PLAYER::GET_PLAYER_WANTED_LEVEL(player) < 5)
				{
					PLAYER::SET_PLAYER_WANTED_LEVEL(player, PLAYER::GET_PLAYER_WANTED_LEVEL(player) + 1, 0);
					PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(player, 0);
					set_status_text("wanted up");
				}
				break;
				// 被通缉
			case 6:
				if (bPlayerExists && PLAYER::GET_PLAYER_WANTED_LEVEL(player) > 0)
				{
					PLAYER::SET_PLAYER_WANTED_LEVEL(player, PLAYER::GET_PLAYER_WANTED_LEVEL(player) - 1, 0);
					PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(player, 0);
					set_status_text("wanted down");
				}
				break;
				// 可切换功能
			default:
				if (lines[activeLineIndexPlayer].pState)
					*lines[activeLineIndexPlayer].pState = !(*lines[activeLineIndexPlayer].pState);
				if (lines[activeLineIndexPlayer].pUpdated)
					*lines[activeLineIndexPlayer].pUpdated = true;
			}
			waitTime = 200;
		}
		else
			if (bBack || trainer_switch_pressed())
			{
				menu_beep();
				break;
			}
			else
				if (bUp)
				{
					menu_beep();
					if (activeLineIndexPlayer == 0)
						activeLineIndexPlayer = lineCount;
					activeLineIndexPlayer--;
					waitTime = 150;
				}
				else
					if (bDown)
					{
						menu_beep();
						activeLineIndexPlayer++;
						if (activeLineIndexPlayer == lineCount)
							activeLineIndexPlayer = 0;
						waitTime = 150;
					}
	}
}

int activeLineIndexWeapon = 0;

void process_weapon_menu()
{
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(u8"武器选项已打开");
	// 提示声音
	PlayFrontend("Phone_SoundSet_Default", "Text_Arrive_Tone");

	UI::_DRAW_NOTIFICATION(0, 0);
	const float lineWidth = 250.0;
	const int lineCount = 6;

	std::string caption = u8"武器选项";

	static struct {
		LPCSTR		text;
		bool* pState;
		bool* pUpdated;
	} lines[lineCount] = {
		{u8"全副武装					    ",	NULL,						  NULL},
		{u8"无需重新加载				    ",		&featureWeaponNoReload,		  NULL},
		{u8"发射弹药					    ",		&featureWeaponFireAmmo,		  NULL},
		{u8"爆炸性弹药				    ",  &featureWeaponExplosiveAmmo,  NULL},
		{u8"爆炸性近战				    ", &featureWeaponExplosiveMelee, NULL},
		{u8"车载火箭					    ", &featureWeaponVehRockets,	  NULL}
	};

	static LPCSTR weaponNames[] = {
		"WEAPON_APPISTOL","WEAPON_COMBATPISTOL","WEAPON_PISTOL","WEAPON_BOTTLE","WEAPON_CROWBAR","WEAPON_GOLFCLUB","","WEAPON_BAT","WEAPON_HAMMER","WEAPON_NIGHTSTICK","WEAPON_KNIFE",
		"WEAPON_PUMPSHOTGUN","WEAPON_COMBATMG","WEAPON_MG","WEAPON_ADVANCEDRIFLE","WEAPON_CARBINERIFLE","WEAPON_ASSAULTRIFLE","WEAPON_ASSAULTSMG","WEAPON_SMG","WEAPON_MICROSMG","WEAPON_REVOLVER","WEAPON_PISTOL50",
		"WEAPON_STICKYBOMB","WEAPON_GRENADE","WEAPON_MINIGUN","WEAPON_RPG","WEAPON_GRENADELAUNCHER","WEAPON_HEAVYSNIPER","WEAPON_SNIPERRIFLE","WEAPON_STUNGUN","WEAPON_BULLPUPSHOTGUN","WEAPON_ASSAULTSHOTGUN","WEAPON_SAWNOFFSHOTGUN",
		"WEAPON_HOMINGLAUNCHER","WEAPON_BULLPUPRIFLE","WEAPON_HEAVYPISTOL","WEAPON_SPECIALCARBINE","WEAPON_SNSPISTOL","WEAPON_PETROLCAN","WEAPON_FIREEXTINGUISHER","WEAPON_MOLOTOV","WEAPON_FLARE","WEAPON_FLAREGUN","WEAPON_SMOKEGRENADE",
		"WEAPON_RAILGUN","WEAPON_HATCHET","WEAPON_GUSENBERG","WEAPON_HEAVYSHOTGUN","WEAPON_MARKSMANRIFLE","WEAPON_MUSKET","WEAPON_FIREWORK","WEAPON_DAGGER","WEAPON_VINTAGEPISTOL","WEAPON_SNOWBALL","WEAPON_PROXMINE",
		"WEAPON_PISTOL_MK2","WEAPON_AUTOSHOTGUN","WEAPON_BATTLEAXE","WEAPON_COMPACTLAUNCHER","WEAPON_MINISMG","WEAPON_PIPEBOMB","WEAPON_POOLCUE","WEAPON_WRENCH","WEAPON_STINGER","WEAPON_BZGAS","WEAPON_BALL",
		"WEAPON_PUMPSHOTGUN_MK2","WEAPON_BULLPUPRIFLE_MK2","WEAPON_SPECIALCARBINE_MK2","WEAPON_REVOLVER_MK2","WEAPON_HEAVYSNIPER_MK2","WEAPON_COMBATMG_MK2","WEAPON_MARKSMANRIFLE_MK2","WEAPON_CARBINERIFLE_MK2","WEAPON_ASSAULTRIFLE_MK2","WEAPON_SMG_MK2","WEAPON_SNSPISTOL_MK2"
	
	};

	DWORD waitTime = 150;
	while (true)
	{
		// timed menu draw, used for pause after active line switch
		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			// draw menu
			draw_menu_line(caption, lineWidth, 15.0, 15.0, 25.0, 75.0, false, true);
			char caption2[32];
			sprintf_s(caption2, u8"HOME						%d / %d", activeLineIndexWeapon + 1, lineCount);
			about = true;//启用独有约束色
			draw_menu_line(caption2, lineWidth, 2.0, 70.0, 25.0, 5.0, false, false);
			about = false;//关闭独有约束色
			for (int i = 0; i < lineCount; i++)
				if (i != activeLineIndexWeapon)
					draw_menu_line(line_as_str(lines[i].text, lines[i].pState),
						lineWidth, 5.0, 91. + i * 27.5, 25.0, 9.0, false, false);
			draw_menu_line(line_as_str(lines[activeLineIndexWeapon].text, lines[activeLineIndexWeapon].pState),
				lineWidth , 5.0, 91. + activeLineIndexWeapon * 27.5, 25.0, 9.0, true, false);
			
			Bottom = true;
			draw_menu_line(u8"1.58   	   NEVERLOSE 免费		0.2.1", lineWidth, 5.0, 257.5, 25.0, 5.0, false, false);
			Bottom = false;

			update_features();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;

		// process buttons
		bool bSelect, bBack, bUp, bDown;
		get_button_state(&bSelect, &bBack, &bUp, &bDown, NULL, NULL);
		if (bSelect)
		{
			menu_beep();

			// 公共变量
			BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
			Player player = PLAYER::PLAYER_ID();
			Ped playerPed = PLAYER::PLAYER_PED_ID();

			switch (activeLineIndexWeapon)
			{
			case 0:
				for (int i = 0; i < sizeof(weaponNames) / sizeof(weaponNames[0]); i++)
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(playerPed, GAMEPLAY::GET_HASH_KEY((char*)weaponNames[i]), 1000, 0);
				set_status_text("all weapon added");
				break;
				// 可切换功能
			default:
				if (lines[activeLineIndexWeapon].pState)
					*lines[activeLineIndexWeapon].pState = !(*lines[activeLineIndexWeapon].pState);
				if (lines[activeLineIndexWeapon].pUpdated)
					*lines[activeLineIndexWeapon].pUpdated = true;
			}
			waitTime = 200;
		}
		else
			if (bBack || trainer_switch_pressed())
			{
				menu_beep();
				break;
			}
			else
				if (bUp)
				{
					menu_beep();
					if (activeLineIndexWeapon == 0)
						activeLineIndexWeapon = lineCount;
					activeLineIndexWeapon--;
					waitTime = 150;
				}
				else
					if (bDown)
					{
						menu_beep();
						activeLineIndexWeapon++;
						if (activeLineIndexWeapon == lineCount)
							activeLineIndexWeapon = 0;
						waitTime = 150;
					}
	}
}

LPCSTR vehicleModels[40][10] = {
	{"NINEF", "NINEF2", "BLISTA", "ASEA", "ASEA2", "BOATTRAILER", "BUS", "ARMYTANKER", "ARMYTRAILER", "ARMYTRAILER2"},
	{"SUNTRAP", "COACH", "AIRBUS", "ASTEROPE", "AIRTUG", "AMBULANCE", "BARRACKS", "BARRACKS2", "BALLER", "BALLER2"},
	{"BJXL", "BANSHEE", "BENSON", "BFINJECTION", "BIFF", "BLAZER", "BLAZER2", "BLAZER3", "BISON", "BISON2"},
	{"BISON3", "BOXVILLE", "BOXVILLE2", "BOXVILLE3", "BOBCATXL", "BODHI2", "BUCCANEER", "BUFFALO", "BUFFALO2", "BULLDOZER"},
	{"BULLET", "BLIMP", "BURRITO", "BURRITO2", "BURRITO3", "BURRITO4", "BURRITO5", "CAVALCADE", "CAVALCADE2", "POLICET"},
	{"GBURRITO", "CABLECAR", "CADDY", "CADDY2", "CAMPER", "CARBONIZZARE", "CHEETAH", "COMET2", "COGCABRIO", "COQUETTE"},
	{"CUTTER", "GRESLEY", "DILETTANTE", "DILETTANTE2", "DUNE", "DUNE2", "HOTKNIFE", "DLOADER", "DUBSTA", "DUBSTA2"},
	{"DUMP", "RUBBLE", "DOCKTUG", "DOMINATOR", "EMPEROR", "EMPEROR2", "EMPEROR3", "ENTITYXF", "EXEMPLAR", "ELEGY2"},
	{"F620", "FBI", "FBI2", "FELON", "FELON2", "FELTZER2", "FIRETRUK", "FLATBED", "FORKLIFT", "FQ2"},
	{"FUSILADE", "FUGITIVE", "FUTO", "GRANGER", "GAUNTLET", "HABANERO", "HAULER", "HANDLER", "INFERNUS", "INGOT"},
	{"INTRUDER", "ISSI2", "JACKAL", "JOURNEY", "JB700", "KHAMELION", "LANDSTALKER", "LGUARD", "MANANA", "MESA"},
	{"MESA2", "MESA3", "CRUSADER", "MINIVAN", "MIXER", "MIXER2", "MONROE", "MOWER", "MULE", "MULE2"},
	{"ORACLE", "ORACLE2", "PACKER", "PATRIOT", "PBUS", "PENUMBRA", "PEYOTE", "PHANTOM", "PHOENIX", "PICADOR"},
	{"POUNDER", "POLICE", "POLICE4", "POLICE2", "POLICE3", "POLICEOLD1", "POLICEOLD2", "PONY", "PONY2", "PRAIRIE"},
	{"PRANGER", "PREMIER", "PRIMO", "PROPTRAILER", "RANCHERXL", "RANCHERXL2", "RAPIDGT", "RAPIDGT2", "RADI", "RATLOADER"},
	{"REBEL", "REGINA", "REBEL2", "RENTALBUS", "RUINER", "RUMPO", "RUMPO2", "RHINO", "RIOT", "RIPLEY"},
	{"ROCOTO", "ROMERO", "SABREGT", "SADLER", "SADLER2", "SANDKING", "SANDKING2", "SCHAFTER2", "SCHWARZER", "SCRAP"},
	{"SEMINOLE", "SENTINEL", "SENTINEL2", "ZION", "ZION2", "SERRANO", "SHERIFF", "SHERIFF2", "SPEEDO", "SPEEDO2"},
	{"STANIER", "STINGER", "STINGERGT", "STOCKADE", "STOCKADE3", "STRATUM", "SULTAN", "SUPERD", "SURANO", "SURFER"},
	{"SURFER2", "SURGE", "TACO", "TAILGATER", "TAXI", "TRASH", "TRACTOR", "TRACTOR2", "TRACTOR3", "GRAINTRAILER"},
	{"BALETRAILER", "TIPTRUCK", "TIPTRUCK2", "TORNADO", "TORNADO2", "TORNADO3", "TORNADO4", "TOURBUS", "TOWTRUCK", "TOWTRUCK2"},
	{"UTILLITRUCK", "UTILLITRUCK2", "UTILLITRUCK3", "VOODOO2", "WASHINGTON", "STRETCH", "YOUGA", "ZTYPE", "SANCHEZ", "SANCHEZ2"},
	{"SCORCHER", "TRIBIKE", "TRIBIKE2", "TRIBIKE3", "FIXTER", "CRUISER", "BMX", "POLICEB", "AKUMA", "CARBONRS"},
	{"BAGGER", "BATI", "BATI2", "RUFFIAN", "DAEMON", "DOUBLE", "PCJ", "VADER", "VIGERO", "FAGGIO2"},
	{"HEXER", "ANNIHILATOR", "BUZZARD", "BUZZARD2", "CARGOBOB", "CARGOBOB2", "CARGOBOB3", "SKYLIFT", "POLMAV", "MAVERICK"},
	{"NEMESIS", "FROGGER", "FROGGER2", "CUBAN800", "DUSTER", "STUNT", "MAMMATUS", "JET", "SHAMAL", "LUXOR"},
	{"TITAN", "LAZER", "CARGOPLANE", "SQUALO", "MARQUIS", "DINGHY", "DINGHY2", "JETMAX", "PREDATOR", "TROPIC"},
	{"SEASHARK", "SEASHARK2", "SUBMERSIBLE", "TRAILERS", "TRAILERS2", "TRAILERS3", "TVTRAILER", "RAKETRAILER", "TANKER", "TRAILERLOGS"},
	{"TR2", "TR3", "TR4", "TRFLAT", "TRAILERSMALL", "VELUM", "ADDER", "VOLTIC", "VACCA", "BIFTA"},
	{ "SPEEDER", "PARADISE", "KALAHARI", "JESTER", "TURISMOR", "VESTRA", "ALPHA", "HUNTLEY", "THRUST", "MASSACRO" },
	{ "MASSACRO2", "ZENTORNO", "BLADE", "GLENDALE", "PANTO", "PIGALLE", "WARRENER", "RHAPSODY", "DUBSTA3", "MONSTER" },
	{ "SOVEREIGN", "INNOVATION", "HAKUCHOU", "FUROREGT", "MILJET", "COQUETTE2", "BTYPE", "BUFFALO3", "DOMINATOR2", "GAUNTLET2" },
	{ "MARSHALL", "DUKES", "DUKES2", "STALION", "STALION2", "BLISTA2", "BLISTA3", "DODO", "SUBMERSIBLE2", "HYDRA" },
	{ "INSURGENT", "INSURGENT2", "TECHNICAL", "SAVAGE", "VALKYRIE", "KURUMA", "KURUMA2", "JESTER2", "CASCO", "VELUM2" },
	{ "GUARDIAN", "ENDURO", "LECTRO", "SLAMVAN", "SLAMVAN2", "RATLOADER2", "SWIFT2", "LUXOR2", "FELTZER3", "OSIRIS" },
	{ "VIRGO", "WINDSOR", "BESRA", "SWIFT", "BLIMP2", "VINDICATOR", "TORO", "T20", "COQUETTE3", "CHINO" },
	{ "BRAWLER", "BUCCANEER2", "CHINO2", "FACTION", "FACTION2", "MOONBEAM", "MOONBEAM2", "PRIMO2", "VOODOO", "LURCHER" },
	{ "BTYPE2", "BALLER3", "BALLER4", "BALLER5", "BALLER6", "CARGOBOB4", "COG55", "COG552", "COGNOSCENTI", "COGNOSCENTI2" },
	{ "DINGHY4", "LIMO2", "MAMBA", "NIGHTSHADE", "SCHAFTER3", "SCHAFTER4", "SCHAFTER5", "SCHAFTER6", "SEASHARK3", "SPEEDER2" },
	{ "SUPERVOLITO", "SUPERVOLITO2", "TORO2", "TROPIC2", "VALKYRIE2", "VERLIERER2", "TAMPA", "BANSHEE2", "SULTANRS", "BTYPE3" }
};

int carspawnActiveLineIndex = 0;
int carspawnActiveItemIndex = 0;

bool process_carspawn_menu()
{
	DWORD waitTime = 150;
	const int lineCount = 40;
	const int itemCount = 10;
	const int itemCountLastLine = 10;
	const float lineWidth = 250.0;
	while (true)
	{
		// timed menu draw, used for pause after active line switch
		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			// draw menu
			draw_menu_line(u8"刷出载具", lineWidth, 15.0, 15.0, 25.0, 75.0, false, true);
			char caption2[32];
			sprintf_s(caption2, u8"HOME						%d / %d", carspawnActiveLineIndex + 1, lineCount);
			about = true;//启用独有约束色
			draw_menu_line(caption2, lineWidth, 2.0, 70.0, 25.0, 5.0, false, false);
			about = false;//关闭独有约束色
			for (int i = 0; i < itemCount; i++)
				if (strlen(vehicleModels[carspawnActiveLineIndex][i]))
					draw_menu_line(vehicleModels[carspawnActiveLineIndex][i], 100.0, 5.0, 200.0, 100.0 + i * 110.0, 5.0, i == carspawnActiveItemIndex, false, false);

			update_features();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;

		bool bSelect, bBack, bUp, bDown, bLeft, bRight;
		get_button_state(&bSelect, &bBack, &bUp, &bDown, &bLeft, &bRight);

		if (bSelect)
		{
			menu_beep();
			LPCSTR modelName = vehicleModels[carspawnActiveLineIndex][carspawnActiveItemIndex];
			DWORD model = GAMEPLAY::GET_HASH_KEY((char*)modelName);
			if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_A_VEHICLE(model))
			{
				STREAMING::REQUEST_MODEL(model);
				while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(0);
				Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0, 5.0, 0.0);
				Vehicle veh = VEHICLE::CREATE_VEHICLE(model, coords.x, coords.y, coords.z, 0.0, 1, 1);
				VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);

				if (featureVehWrapInSpawned)
				{
					ENTITY::SET_ENTITY_HEADING(veh, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
					PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
				}

				WAIT(0);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
				ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&veh);

				char statusText[32];
				sprintf_s(statusText, "%s spawned", modelName);
				set_status_text(statusText);

				return true;
			}
		}
		else
			if (bBack)
			{
				menu_beep();
				break;
			}
			else
				if (bRight)
				{
					menu_beep();
					carspawnActiveItemIndex++;
					int itemsMax = (carspawnActiveLineIndex == (lineCount - 1)) ? itemCountLastLine : itemCount;
					if (carspawnActiveItemIndex == itemsMax)
						carspawnActiveItemIndex = 0;
					waitTime = 100;
				}
				else
					if (bLeft)
					{
						menu_beep();
						if (carspawnActiveItemIndex == 0)
							carspawnActiveItemIndex = (carspawnActiveLineIndex == (lineCount - 1)) ? itemCountLastLine : itemCount;
						carspawnActiveItemIndex--;
						waitTime = 100;
					}
					else
						if (bUp)
						{
							menu_beep();
							if (carspawnActiveLineIndex == 0)
								carspawnActiveLineIndex = lineCount;
							carspawnActiveLineIndex--;
							waitTime = 200;
						}
						else
							if (bDown)
							{
								menu_beep();
								carspawnActiveLineIndex++;
								if (carspawnActiveLineIndex == lineCount)
									carspawnActiveLineIndex = 0;
								waitTime = 200;
							}
		if (carspawnActiveLineIndex == (lineCount - 1))
			if (carspawnActiveItemIndex >= itemCountLastLine)
				carspawnActiveItemIndex = 0;
	}
	return false;
}


int activeLineIndexVeh = 0;

void process_veh_menu()
{
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(u8"交通选项已打开");
	// 提示声音
	PlayFrontend("Phone_SoundSet_Default", "Text_Arrive_Tone");

	UI::_DRAW_NOTIFICATION(0, 0);
	const float lineWidth = 250.0;
	const int lineCount = 15;

	std::string caption = u8"交通工具";

	static struct {
		LPCSTR		text;
		bool* pState;
		bool* pUpdated;
	} lines[lineCount] = {
		{u8"DLC							  >",		NULL, NULL},
		{u8"汽车							  >",		NULL, NULL},
		{u8"火车							  >",		NULL, NULL},
		{u8"摩托车						  >",		NULL, NULL},
		{u8"飞机							  >",		NULL, NULL},
		{u8"直升机						  >",		NULL, NULL},
		{u8"船舶							  >",		NULL, NULL},
		{u8"自行车						  >",		NULL, NULL},
		{u8"随意画",	NULL, NULL},
		{u8"修理",				NULL, NULL},
		{u8"安全带				           ",		&featureVehSeatbelt, &featureVehSeatbeltUpdated},
		{u8"刷出就出生载具中			   ",	&featureVehWrapInSpawned, NULL},
		{u8"无敌载具				           ",		&featureVehInvincible, &featureVehInvincibleUpdated},
		{u8"防爆车轮					   ",	&featureVehInvincibleWheels, &featureVehInvincibleWheelsUpdated},
		{u8"提速					           ",		&featureVehSpeedBoost, NULL}
	};

	DWORD waitTime = 150;
	while (true)
	{
		// timed menu draw, used for pause after active line switch
		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			// draw menu
			draw_menu_line(caption, lineWidth, 15.0, 15.0, 25.0, 75.0, false, true);
			char caption2[32];
			sprintf_s(caption2, u8"HOME					    %d / %d", activeLineIndexVeh + 1, lineCount);
			about = true;//启用独有约束色
			draw_menu_line(caption2, lineWidth, 2.0, 70.0, 25.0, 5.0, false, false);
			about = false;//关闭独有约束色
			for (int i = 0; i < lineCount; i++)
				if (i != activeLineIndexVeh)
					draw_menu_line(line_as_str(lines[i].text, lines[i].pState),
						lineWidth, 5.0, 91. + i * 27.5, 25.0, 9.0, false, false);
			draw_menu_line(line_as_str(lines[activeLineIndexVeh].text, lines[activeLineIndexVeh].pState),
				lineWidth, 5.0, 91. + activeLineIndexVeh * 27.5, 25.0, 9.0, true, false);
			Bottom = true;
			draw_menu_line(u8"1.58   	   NEVERLOSE 免费		0.2.1", lineWidth, 5.0, 505.5, 25.0, 5.0, false, false);
			Bottom = false;

			update_features();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;

		// process buttons
		bool bSelect, bBack, bUp, bDown;
		get_button_state(&bSelect, &bBack, &bUp, &bDown, NULL, NULL);
		if (bSelect)
		{
			menu_beep();

			// common variables
			BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
			Player player = PLAYER::PLAYER_ID();
			Ped playerPed = PLAYER::PLAYER_PED_ID();
			//if (process_carspawn_menu()) return
			switch (activeLineIndexVeh)
			{
			case 0:
				;
				break;
			case 1:process_Standardcar_menu();
				break;
			case 2:process_train_menu()
				;
				break;
			case 3:process_motorcycle_menu()
				  ;
				break;
			case 4:process_aircraft_menu()
				 ;
				break;
			case 5:process_helicopter_menu()
				;
				break;
			case 6:process_aship_menu()
				;
				break;
			case 7:process_Bicycle_menu()
				;
				break;
			case 8:
				if (bPlayerExists)
				{
					if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
					{
						Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
						VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, rand() % 255, rand() % 255, rand() % 255);
						if (VEHICLE::GET_IS_VEHICLE_PRIMARY_COLOUR_CUSTOM(veh))
							VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, rand() % 255, rand() % 255, rand() % 255);
					}
					else
					{
						set_status_text("player isn't in a vehicle");
					}
				}
				;
				break;
			case 9:
				if (bPlayerExists)
					if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
						VEHICLE::SET_VEHICLE_FIXED(PED::GET_VEHICLE_PED_IS_USING(playerPed));
					else
						set_status_text("player isn't in a vehicle")
				
				;
				break;
			case 10:
				;
				break;
			case 11:
				;
				break;
			case 12:
				;
				break;
			case 13:
				;
				break;
			case 14:
				;
				break;
			default:
				if (lines[activeLineIndexVeh].pState)
					*lines[activeLineIndexVeh].pState = !(*lines[activeLineIndexVeh].pState);
				if (lines[activeLineIndexVeh].pUpdated)
					*lines[activeLineIndexVeh].pUpdated = true;
			}
			waitTime = 200;
		}
		else
			if (bBack || trainer_switch_pressed())
			{
				menu_beep();
				break;
			}
			else
				if (bUp)
				{
					menu_beep();
					if (activeLineIndexVeh == 0)
						activeLineIndexVeh = lineCount;
					activeLineIndexVeh--;
					waitTime = 150;
				}
				else
					if (bDown)
					{
						menu_beep();
						activeLineIndexVeh++;
						if (activeLineIndexVeh == lineCount)
							activeLineIndexVeh = 0;
						waitTime = 150;
					}
	}
}

int activeLineIndexWorld = 0;

void process_world_menu()
{
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(u8"世界选项已打开");
	// 提示声音
	PlayFrontend("Phone_SoundSet_Default", "Text_Arrive_Tone");

	UI::_DRAW_NOTIFICATION(0, 0);

	const float lineWidth = 250.0;
	const int lineCount = 5;

	std::string caption = u8"世界";

	static struct {
		LPCSTR		text;
		bool* pState;
		bool* pUpdated;
	} lines[lineCount] = {
		{u8"月球引力					  ",	&featureWorldMoonGravity,	NULL},
		{u8"随机警察					  ",		&featureWorldRandomCops,	NULL},
		{u8"随机列车					  ",	&featureWorldRandomTrains,	NULL},
		{u8"随机船只					  ",	&featureWorldRandomBoats,	NULL},
		{u8"垃圾车				         ",	&featureWorldGarbageTrucks,	NULL}
	};

	DWORD waitTime = 150;
	while (true)
	{
		// timed menu draw, used for pause after active line switch
		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			// draw menu
			draw_menu_line(caption, lineWidth, 15.0, 15.0, 25.0, 105.0, false, true);
			char caption2[32];
			sprintf_s(caption2, u8"HOME						%d / %d", activeLineIndexWorld + 1, lineCount);
			about = true;//启用独有约束色
			draw_menu_line(caption2, lineWidth, 2.0, 70.0, 25.0, 5.0, false, false);
			about = false;//关闭独有约束色
			for (int i = 0; i < lineCount; i++)
				if (i != activeLineIndexWorld)
					draw_menu_line(line_as_str(lines[i].text, lines[i].pState),
						lineWidth, 5.0, 91. + i * 27.5, 25.0, 9.0, false, false);
			draw_menu_line(line_as_str(lines[activeLineIndexWorld].text, lines[activeLineIndexWorld].pState),
				lineWidth , 5.0, 91. + activeLineIndexWorld * 27.5, 25.0, 9.0, true, false);
			Bottom = true;
			draw_menu_line(u8"1.58   	   NEVERLOSE 免费		0.2.1", lineWidth, 5.0, 230.0, 25.0, 5.0, false, false);
			Bottom = false;
			update_features();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;

		// process buttons
		bool bSelect, bBack, bUp, bDown;
		get_button_state(&bSelect, &bBack, &bUp, &bDown, NULL, NULL);
		if (bSelect)
		{
			menu_beep();
			switch (activeLineIndexWorld)
			{
			case 0:
				featureWorldMoonGravity = !featureWorldMoonGravity;
				GAMEPLAY::SET_GRAVITY_LEVEL(featureWorldMoonGravity ? 2 : 0);
				break;
			case 1:
				// 正在更新功能中设置featureWorldRandomCops
				PED::SET_CREATE_RANDOM_COPS(!featureWorldRandomCops);
				break;
			case 2:
				featureWorldRandomTrains = !featureWorldRandomTrains;
				VEHICLE::SET_RANDOM_TRAINS(featureWorldRandomTrains);
				break;
			case 3:
				featureWorldRandomBoats = !featureWorldRandomBoats;
				VEHICLE::SET_RANDOM_BOATS(featureWorldRandomBoats);
				break;
			case 4:
				featureWorldGarbageTrucks = !featureWorldGarbageTrucks;
				VEHICLE::SET_GARBAGE_TRUCKS(featureWorldGarbageTrucks);
				break;
			}
			waitTime = 200;
		}
		else
			if (bBack || trainer_switch_pressed())
			{
				menu_beep();
				break;
			}
			else
				if (bUp)
				{
					menu_beep();
					if (activeLineIndexWorld == 0)
						activeLineIndexWorld = lineCount;
					activeLineIndexWorld--;
					waitTime = 150;
				}
				else
					if (bDown)
					{
						menu_beep();
						activeLineIndexWorld++;
						if (activeLineIndexWorld == lineCount)
							activeLineIndexWorld = 0;
						waitTime = 150;
					}
	}
}

int activeLineIndexTime = 0;

void process_time_menu()
{
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(u8"时间选项已打开");
	// 提示声音
	PlayFrontend("Phone_SoundSet_Default", "Text_Arrive_Tone");

	UI::_DRAW_NOTIFICATION(0, 0);

	const float lineWidth = 250.0;
	const int lineCount = 4;

	std::string caption = u8"时间";

	static struct {
		LPCSTR		text;
		bool* pState;
		bool* pUpdated;
	} lines[lineCount] = {
		{u8"一小时前",	 NULL,				 NULL},
		{u8"一小时后",	 NULL,				 NULL},
		{u8"时钟暂停了				  ",	 &featureTimePaused, &featureTimePausedUpdated},
		{u8"与系统同步				  ", &featureTimeSynced, NULL}
	};

	DWORD waitTime = 150;
	while (true)
	{
		// timed menu draw, used for pause after active line switch
		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			// draw menu
			draw_menu_line(caption, lineWidth, 15.0, 15.0, 25.0, 105.0, false, true);
			char caption2[32];
			sprintf_s(caption2, u8"HOME						%d / %d", activeLineIndexTime + 1, lineCount);
			about = true;//启用独有约束色
			draw_menu_line(caption2, lineWidth, 2.0, 70.0, 25.0, 5.0, false, false);
			about = false;//关闭独有约束色
			for (int i = 0; i < lineCount; i++)
				if (i != activeLineIndexTime)
					draw_menu_line(line_as_str(lines[i].text, lines[i].pState),
						lineWidth, 5.0, 91. + i * 27.5, 25.0, 9.0, false, false);
			draw_menu_line(line_as_str(lines[activeLineIndexTime].text, lines[activeLineIndexTime].pState),
				lineWidth , 5.0, 91. + activeLineIndexTime * 27.5, 25.0, 9.0, true, false);
			Bottom = true;
			draw_menu_line(u8"1.58   	   NEVERLOSE 免费		0.2.1", lineWidth, 5.0, 202.5, 25.0, 5.0, false, false);
			Bottom = false;
			update_features();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;

		// process buttons
		bool bSelect, bBack, bUp, bDown;
		get_button_state(&bSelect, &bBack, &bUp, &bDown, NULL, NULL);
		if (bSelect)
		{
			menu_beep();
			switch (activeLineIndexTime)
			{
				// 前进/后退小时
			case 0:
			case 1:
			{
				int h = TIME::GET_CLOCK_HOURS();
				if (activeLineIndexTime == 0) h = (h == 23) ? 0 : h + 1; else h = (h == 0) ? 23 : h - 1;
				int m = TIME::GET_CLOCK_MINUTES();
				TIME::SET_CLOCK_TIME(h, m, 0);
				char text[32];
				sprintf_s(text, "time %d:%d", h, m);
				set_status_text(text);
			}
			break;
			// switchable features
			default:
				if (lines[activeLineIndexTime].pState)
					*lines[activeLineIndexTime].pState = !(*lines[activeLineIndexTime].pState);
				if (lines[activeLineIndexTime].pUpdated)
					*lines[activeLineIndexTime].pUpdated = true;
			}
			waitTime = 200;
		}
		else
			if (bBack || trainer_switch_pressed())
			{
				menu_beep();
				break;
			}
			else
				if (bUp)
				{
					menu_beep();
					if (activeLineIndexTime == 0)
						activeLineIndexTime = lineCount;
					activeLineIndexTime--;
					waitTime = 150;
				}
				else
					if (bDown)
					{
						menu_beep();
						activeLineIndexTime++;
						if (activeLineIndexTime == lineCount)
							activeLineIndexTime = 0;
						waitTime = 150;
					}
	}
}

int activeLineIndexWeather = 0;

void process_weather_menu()
{
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(u8"天气选项已打开");
	// 提示声音
	PlayFrontend("Phone_SoundSet_Default", "Text_Arrive_Tone");

	UI::_DRAW_NOTIFICATION(0, 0);

	const float lineWidth = 250.0;
	const int lineCount = 16;

	std::string caption = u8"天气";

	static struct {
		LPCSTR		text;
		bool* pState;
		bool* pUpdated;
	} lines[lineCount] = {
		{u8"风					 ",	&featureWeatherWind,	NULL},
		{u8"设定持续时间				  ",  &featureWeatherPers,	NULL},
		{u8"阳光灿烂",	 NULL,					NULL},
		{u8"清楚的",		 NULL,					NULL},
		{u8"云",		 NULL,					NULL},
		{u8"烟雾",		 NULL,					NULL},
		{u8"有雾的",	 	 NULL,					NULL},
		{u8"阴天",	 NULL,					NULL},
		{u8"雨",		 NULL,					NULL},
		{u8"打雷",		 NULL,					NULL},
		{u8"清理",	 NULL,					NULL},
		{u8"中立的",		 NULL,					NULL},
		{u8"雪",		 NULL,					NULL},
		{u8"暴风雪",	 NULL,					NULL},
		{u8"雪光",	 NULL,					NULL},
		{u8"圣诞节",		 NULL,					NULL}
	};


	DWORD waitTime = 150;
	while (true)
	{

		
		// timed menu draw, used for pause after active line switch
		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			// draw menu
			draw_menu_line(caption, lineWidth, 15.0, 15.0, 25.0, 105.0, false, true);
			char caption2[32];
			sprintf_s(caption2, u8"HOME					   %d / %d", activeLineIndexWeather + 1, lineCount);
			about = true;//启用独有约束色
			draw_menu_line(caption2, lineWidth, 2.0, 70.0, 25.0, 5.0, false, false);
			about = false;//关闭独有约束色
			for (int i = 0; i < lineCount; i++)
				if (i != activeLineIndexWeather)
					draw_menu_line(line_as_str(lines[i].text, lines[i].pState),
						lineWidth, 5.0, 91. + i * 27.5, 25.0, 9.0, false, false);
			draw_menu_line(line_as_str(lines[activeLineIndexWeather].text, lines[activeLineIndexWeather].pState),
				lineWidth, 5.0, 91. + activeLineIndexWeather * 27.5, 25.0, 9.0, true, false);
			Bottom = true;
			draw_menu_line(u8"1.58   	   NEVERLOSE 免费		0.2.1", lineWidth, 5.0, 533.0, 25.0, 5.0, false, false);
			Bottom = false;
			update_features();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;

		// process buttons
		bool bSelect, bBack, bUp, bDown;
		get_button_state(&bSelect, &bBack, &bUp, &bDown, NULL, NULL);
		if (bSelect)
		{
			menu_beep();
			switch (activeLineIndexWeather)
			{
				// 风
			case 0:
				featureWeatherWind = !featureWeatherWind;
				if (featureWeatherWind)
				{
					GAMEPLAY::SET_WIND(1.0);
					GAMEPLAY::SET_WIND_SPEED(11.99);
					GAMEPLAY::SET_WIND_DIRECTION(ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
				}
				else
				{
					GAMEPLAY::SET_WIND(0.0);
					GAMEPLAY::SET_WIND_SPEED(0.0);
				}
				break;
				// 设置持久性
			case 1:
				featureWeatherPers = !featureWeatherPers;
				break;
				// 设定天气
			default:
				GAMEPLAY::CLEAR_OVERRIDE_WEATHER();
				if (featureWeatherPers)
				{
					GAMEPLAY::SET_OVERRIDE_WEATHER((char*)lines[activeLineIndexWeather].text);
				}
				else
				{
					GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST((char*)lines[activeLineIndexWeather].text);
					GAMEPLAY::CLEAR_WEATHER_TYPE_PERSIST();
				}
				set_status_text(lines[activeLineIndexWeather].text);
			}
			waitTime = 200;
		}
		else
			if (bBack || trainer_switch_pressed())
			{
				menu_beep();
				break;
			}
			else
				if (bUp)
				{
					menu_beep();
					if (activeLineIndexWeather == 0)
						activeLineIndexWeather = lineCount;
					activeLineIndexWeather--;
					waitTime = 150;
				}
				else
					if (bDown)
					{
						menu_beep();
						activeLineIndexWeather++;
						if (activeLineIndexWeather == lineCount)
							activeLineIndexWeather = 0;
						waitTime = 150;
					}
	}
}

int activeLineIndexMisc = 0;

void process_misc_menu()
{
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(u8"杂项选项已打开");
	// 提示声音
	PlayFrontend("Phone_SoundSet_Default", "Text_Arrive_Tone");

	UI::_DRAW_NOTIFICATION(0, 0);
	const float lineWidth = 250.0;
	const int lineCount = 2;

	std::string caption = u8"杂项";

	static struct {
		LPCSTR		text;
		bool* pState;
		bool* pUpdated;
	} lines[lineCount] = {
		{u8"下一个广播轨道",	NULL,					NULL},
		{u8"隐藏抬头显示器			  ",			&featureMiscHideHud,	NULL}
	};


	DWORD waitTime = 150;
	while (true)
	{
		// timed menu draw, used for pause after active line switch
		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			// draw menu
			draw_menu_line(caption, lineWidth, 15.0, 15.0, 25.0, 105.0, false, true);
			char caption2[32];
			sprintf_s(caption2, u8"HOME						%d / %d", activeLineIndexMisc + 1, lineCount);
			about = true;//启用独有约束色
			draw_menu_line(caption2, lineWidth, 2.0, 70.0, 25.0, 5.0, false, false);
			about = false;//关闭独有约束色
			for (int i = 0; i < lineCount; i++)
				if (i != activeLineIndexMisc)
					draw_menu_line(line_as_str(lines[i].text, lines[i].pState),
						lineWidth, 5.0, 91. + i * 27.5, 25.0, 9.0, false, false);
			draw_menu_line(line_as_str(lines[activeLineIndexMisc].text, lines[activeLineIndexMisc].pState),
				lineWidth, 5.0, 91. + activeLineIndexMisc * 27.5, 25.0, 9.0, true, false);
			Bottom = true;
			draw_menu_line(u8"1.58   	   NEVERLOSE 免费		0.2.1", lineWidth, 5.0, 147.5, 25.0, 5.0, false, false);
			Bottom = false;
			update_features();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;

		// process buttons
		bool bSelect, bBack, bUp, bDown;
		get_button_state(&bSelect, &bBack, &bUp, &bDown, NULL, NULL);
		if (bSelect)
		{
			menu_beep();
			switch (activeLineIndexMisc)
			{
				// 下一个广播曲目
			case 0:
				if (ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID()) &&
					PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
					AUDIO::SKIP_RADIO_FORWARD();
				break;
				// switchable features
			default:
				if (lines[activeLineIndexMisc].pState)
					*lines[activeLineIndexMisc].pState = !(*lines[activeLineIndexMisc].pState);
				if (lines[activeLineIndexMisc].pUpdated)
					*lines[activeLineIndexMisc].pUpdated = true;
			}
			waitTime = 200;
		}
		else
			if (bBack || trainer_switch_pressed())
			{
				menu_beep();
				break;
			}
			else
				if (bUp)
				{
					menu_beep();
					if (activeLineIndexMisc == 0)
						activeLineIndexMisc = lineCount;
					activeLineIndexMisc--;
					waitTime = 150;
				}
				else
					if (bDown)
					{
						menu_beep();
						activeLineIndexMisc++;
						if (activeLineIndexMisc == lineCount)
							activeLineIndexMisc = 0;
						waitTime = 150;
					}
	}
}
int activeLineIndexModel = 0;
void process_model_menu() {

	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(u8"模型选项已打开");
	// 提示声音
	PlayFrontend("Phone_SoundSet_Default", "Text_Arrive_Tone");

	UI::_DRAW_NOTIFICATION(0, 0);

	const float lineWidth = 250.0;
	const int lineCount = 10;

	std::string caption = u8"模型";

	static struct {
		LPCSTR		text;
		bool* pState;
		bool* pUpdated;
	} lines[lineCount] = {
		{u8"家具							  >",	NULL,       NULL},
		{u8"人物							  >",		NULL,	NULL},
		{u8"道路							  >",	NULL,       NULL},
		{u8"车辆							  >",		NULL,	NULL},
		{u8"其他1						  >",	NULL,       NULL},
		{u8"其他2						  >",		NULL,	NULL},
		{u8"其他3						  >",	NULL,       NULL},
		{u8"其他4						  >",		NULL,	NULL},
		{u8"其他5						  >",	NULL,       NULL},
		{u8"其他6						  >",		NULL,	NULL}
		
	};
	DWORD waitTime = 150;
	while (true)
	{
		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			draw_menu_line(caption, lineWidth, 15.0, 15.0, 25.0, 105.0, false, true);
			char caption2[32];
			sprintf_s(caption2, u8"HOME					   %d / %d", activeLineIndexModel + 1, lineCount);
			about = true;//启用独有约束色
			draw_menu_line(caption2, lineWidth, 2.0, 70.0, 25.0, 5.0, false, false);
			about = false;//关闭独有约束色
			for (int i = 0; i < lineCount; i++)
				if (i != activeLineIndexModel)
					draw_menu_line(line_as_str(lines[i].text, lines[i].pState),
						lineWidth, 5.0, 91. + i * 27.5, 25.0, 9.0, false, false);
			draw_menu_line(line_as_str(lines[activeLineIndexModel].text, lines[activeLineIndexModel].pState),
				lineWidth, 5.0, 91. + activeLineIndexModel * 27.5, 25.0, 9.0, true, false);
			Bottom = true;
			draw_menu_line(u8"1.58   	   NEVERLOSE 免费		0.2.1", lineWidth, 5.0, 368.5, 25.0, 5.0, false, false);
			Bottom = false;
			update_features();
			WAIT(0);

		} while (GetTickCount() < maxTickCount);
		waitTime = 0;
		bool bSelect, bBack, bUp, bDown;
		get_button_state(&bSelect, &bBack, &bUp, &bDown, NULL, NULL);
		if (bSelect)
		{
			menu_beep();
			switch (activeLineIndexModel)
			{
				case 0:; break;
				case 1:; break;
				case 2:; break;
				case 3:; break;
				case 4:; break;
				case 5:; break;
				case 6:; break;
				case 7:; break;
				case 8:; break;
				case 9:; break;
			}
			waitTime = 200;
		}
		else
			if (bBack || trainer_switch_pressed())
			{
				menu_beep();
				break;
			}
			else
				if (bUp)
				{
					menu_beep();
					if (activeLineIndexModel == 0)
						activeLineIndexModel = lineCount;
					activeLineIndexModel--;
					waitTime = 150;
				}
				else
					if (bDown)
					{
						menu_beep();
						activeLineIndexModel++;
						if (activeLineIndexModel == lineCount)
							activeLineIndexModel = 0;
						waitTime = 150;
					}
	}

}

int activeLineIndexMain = 0;



void process_main_menu()
{
		//测试 套现成功
		//UI::_SET_SINGLEPLAYER_HUD_CASH(12000, 0);

	//char statusText[32];
	//sprintf_s(statusText, u8"");
	//set_status_text(statusText);

	
	
	const float lineWidth = 250.0;
	const int lineCount = 9;

	std::string caption = u8"NEVERLOSE";
	/*
	game player
bodyguard
delivery
arms
Vehicle
world
time
weather
other
	*/
	static LPCSTR lineCaption[lineCount] = {
		u8"玩家选项					          >",
		u8"武器功能					          >",
		u8"交通选项					          >",
		u8"世界功能					          >",
		u8"时间选项					          >",
		u8"天气功能					          >",
		u8"杂项选项					          >",
		u8"模型功能					          >",
		u8"菜单选项					          >",
	};

	DWORD waitTime = 150;
	while (true)
	{
		// timed menu draw, used for pause after active line switch
		DWORD maxTickCount = GetTickCount() + waitTime;
		do
		{
			// 绘图菜单      字符串标题，行宽度，  行高，  行顶， 行左，文本左，活动，标题
			float titleValue = 0.0;
			draw_menu_line(caption, lineWidth, 15.0, 15.0, 25.0, 75.0, false, true);
			char caption2[32];
			sprintf_s(caption2, u8"HOME						%d / %d", activeLineIndexMain + 1, lineCount);
			about = true;//启用独有约束色
			draw_menu_line(caption2, lineWidth, 2.0, 70.0, 25.0, 5.0, false, false);
			about = false;//关闭独有约束色
			for (int i = 0; i < lineCount; i++)
				if (i != activeLineIndexMain)
					if (i != 9)
						draw_menu_line(lineCaption[i], lineWidth, 5.0, 91. + i * 27.5, 25.0, 9.0, false, false);
					else{
						
						draw_menu_line(lineCaption[i], lineWidth, 5.0, 91. + i * 27.5, 25.0, 9.0, false, false);
						
					}
			draw_menu_line(lineCaption[activeLineIndexMain], lineWidth, 5.0, 91. + activeLineIndexMain * 27.5, 25.0, 9.0, true, false);
			
			Bottom = true;
			draw_menu_line(u8"1.58   	   NEVERLOSE 免费		0.2.1", lineWidth, 5.0, 340.0, 25.0, 5.0, false, false);
			Bottom = false;

			update_features();
			WAIT(0);
		} while (GetTickCount() < maxTickCount);
		waitTime = 0;

		// process buttons
		bool bSelect, bBack, bUp, bDown;
		get_button_state(&bSelect, &bBack, &bUp, &bDown, NULL, NULL);
		if (bSelect)
		{
			menu_beep();
			switch (activeLineIndexMain)
			{
			case 0:
				process_player_menu();
				break;
			case 1:
				process_weapon_menu();
				break;
			case 2:
				process_veh_menu();
				break;
			case 3:
				process_world_menu();
				break;
			case 4:
				process_time_menu();
				break;
			case 5:
				process_weather_menu();
				break;
			case 6:
				process_misc_menu();
				break;
			case 7:
				process_model_menu();
				break;
			}
			
			waitTime = 200;
		}
		else
			if (bBack || trainer_switch_pressed())
			{
				menu_beep();
				break;
			}
			else
				if (bUp)
				{
					menu_beep();
					if (activeLineIndexMain == 0)
						activeLineIndexMain = lineCount;
					activeLineIndexMain--;
					waitTime = 150;
				}
				else
					if (bDown)
					{
						menu_beep();
						activeLineIndexMain++;
						if (activeLineIndexMain == lineCount)
							activeLineIndexMain = 0;
						waitTime = 150;
					}
	}
}

void reset_globals()
{
	activeLineIndexMain =
		activeLineIndexPlayer =
		skinchangerActiveLineIndex =
		skinchangerActiveItemIndex =
		teleportActiveLineIndex =
		activeLineIndexWeapon =
		activeLineIndexVeh =
		carspawnActiveLineIndex =
		carspawnActiveItemIndex =
		activeLineIndexWorld =
		activeLineIndexWeather = 0;

	featurePlayerInvincible =
		featurePlayerInvincibleUpdated =
		featurePlayerNeverWanted =
		featurePlayerIgnored =
		featurePlayerIgnoredUpdated =
		featurePlayerUnlimitedAbility =
		featurePlayerNoNoise =
		featurePlayerNoNoiseUpdated =
		featurePlayerFastSwim =
		featurePlayerFastSwimUpdated =
		featurePlayerFastRun =
		featurePlayerFastRunUpdated =
		featurePlayerSuperJump =
		featureWeaponNoReload =
		featureWeaponFireAmmo =
		featureWeaponExplosiveAmmo =
		featureWeaponExplosiveMelee =
		featureWeaponVehRockets =
		featureVehInvincible =
		featureVehInvincibleUpdated =
		featureVehInvincibleWheels =
		featureVehInvincibleWheelsUpdated =
		featureVehSeatbelt =
		featureVehSeatbeltUpdated =
		featureVehSpeedBoost =
		featureVehWrapInSpawned =
		featureVehmotorcycle = 
		featureVenaircraft =
		featureWorldMoonGravity =
		featureTimePaused =
		featureTimePausedUpdated =
		featureTimeSynced =
		featureWeatherWind =
		featureWeatherPers =
		featureMiscLockRadio =
		featureMiscHideHud = false;

	featureWorldRandomCops =
		featureWorldRandomTrains =
		featureWorldRandomBoats =
		featureWorldGarbageTrucks = true;

	skinchanger_used = false;
}

void main()
{
	reset_globals();
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(u8"GTA5 1.58 线下版本 免费使用");
	// 提示声音
	PlayFrontend("Phone_SoundSet_Default", "Text_Arrive_Tone");

	UI::_DRAW_NOTIFICATION(0, 0);

	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(u8"作者QQ：870993238");
	// 提示声音
	PlayFrontend("Phone_SoundSet_Default", "Text_Arrive_Tone");

	UI::_DRAW_NOTIFICATION(0, 0);

	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(u8"官网：https://q-tai-mu.github.io");
	// 提示声音
	PlayFrontend("Phone_SoundSet_Default", "Text_Arrive_Tone");

	UI::_DRAW_NOTIFICATION(0, 0);
	while (true)
	{
		if (trainer_switch_pressed())
		{
			menu_beep();
			process_main_menu();
		}

		update_features();
		WAIT(0);
	}
}

void ScriptMain()
{
	srand(GetTickCount());
	
	AllocConsole();
	freopen("CON", "w", stdout);
	SetConsoleTitleA("NEVERLOSE logger");//控制台标题
	std::cout << "GTACHEATS started..."<<std::endl;
	std::cout << " _____ _" << std::endl;
	std::cout << "|_   _| |__   ___ _ __   ___  ___ _ __ ___  _ __ ___   __ _ _ __   ___ ___" << std::endl;
	std::cout << "  | | | '_ \ / _ \ '_ \ / _ \/ __| '__/ _ \| '_ ` _ \ / _` | '_ \ / __/ _ \'" << std::endl;
	std::cout << "  | | | | | |  __/ | | |  __/ (__| | | (_) | | | | | | (_| | | | | (_|  __/" << std::endl;
	std::cout << "  |_| |_| |_|\___|_| |_|\___|\___|_|  \___/|_| |_| |_|\__,_|_| |_|\___\___|" << std::endl;
	std::cout << "[GTACHEATS] minHook未启动，已切换scriptHookV..." << std::endl;
	std::cout << "[GTACHEATS] 身份校验未启动，已切换单机模式..." << std::endl;
	std::cout << "[GTACHEATS] UI汉化成功..." << std::endl;
	std::cout << "[GTACHEATS] 菜单布局读取，布局已左上角为基标..." << std::endl;
	std::cout << "[GTACHEATS] MIK 武器 添加至武器菜单..." << std::endl;
	std::cout << "[GTACHEATS] DLC-经典 载具 添加至载具菜单..." << std::endl;
	std::cout << "[GTACHEATS] DLC-2015 载具 添加至载具菜单..." << std::endl;
	std::cout << "[GTACHEATS] DLC-万圣节狂欢 载具 未添加至载具菜单..." << std::endl;
	std::cout << "[GTACHEATS] DLC-Lowriders 载具 未添加至载具菜单..." << std::endl;
	std::cout << "[GTACHEATS] DLC-沙滩狂欢 载具 未添加至载具菜单..." << std::endl;
	std::cout << "[GTACHEATS] DLC-情人节大** 载具 未添加至载具菜单..." << std::endl;
	std::cout << "[GTACHEATS] DLC-高端商务 载具 未添加至载具菜单..." << std::endl;
	std::cout << "[GTACHEATS] DLC-自以为潮 载具 未添加至载具菜单..." << std::endl;
	std::cout << "[GTACHEATS] DLC-美国独立日 载具 未添加至载具菜单..." << std::endl;
	std::cout << "[GTACHEATS] DLC-飞行学院 载具 未添加至载具菜单..." << std::endl;
	std::cout << "[GTACHEATS] DLC-团队生存 载具 未添加至载具菜单..." << std::endl;
	std::cout << "[GTACHEATS] DLC-圣诞节庆 载具 未添加至载具菜单..." << std::endl;
	std::cout << "[GTACHEATS] DLC-次世代回归 载具 未添加至载具菜单..." << std::endl;
	std::cout << "[GTACHEATS] DLC-抢劫任务 载具 未添加至载具菜单..." << std::endl;
	std::cout << "[GTACHEATS] DLC-做我的情人 载具 未添加至载具菜单..." << std::endl;
	std::cout << "[GTACHEATS] DLC-权贵天下 载具 未添加至载具菜单..." << std::endl;
	std::cout << "[GTACHEATS] DLC-不义之财 载具 未添加至载具菜单..." << std::endl;
	std::cout << "[GTACHEATS] DLC-富贵险中求 载具 未添加至载具菜单..." << std::endl;
	std::cout << "[GTACHEATS] DLC-精彩的表演 载具 未添加至载具菜单..." << std::endl;
	std::cout << "[GTACHEATS] DLC-狂野飙客 载具 未添加至载具菜单..." << std::endl;
	std::cout << "[GTACHEATS] DLC-进出口大亨 载具 未添加至载具菜单..." << std::endl;
	std::cout << "[GTACHEATS] DLC-特殊载具巡回赛 载具 未添加至载具菜单..." << std::endl;
	std::cout << "[GTACHEATS] DLC-军火走私 载具 未添加至载具菜单..." << std::endl;
	std::cout << "[GTACHEATS] DLC-走私大爆走 载具 未添加至载具菜单..." << std::endl;
	std::cout << "[GTACHEATS] DLC-末日抢劫 载具 未添加至载具菜单..." << std::endl;
	std::cout << "[GTACHEATS] DLC-南圣安地列斯超级系列赛 载具 未添加至载具菜单..." << std::endl;
	std::cout << "[GTACHEATS] DLC-不夜城 载具 未添加至载具菜单..." << std::endl;
	std::cout << "[GTACHEATS] DLC-竞技场之战 载具 未添加至载具菜单..." << std::endl;
	std::cout << "[GTACHEATS] DLC-名钻假日赌城 载具 未添加至载具菜单..." << std::endl;
	std::cout << "[GTACHEATS] DLC-名钻赌场豪劫 载具 未添加至载具菜单..." << std::endl;
	std::cout << "[GTACHEATS] DLC-洛圣都夏日特辑 载具 未添加至载具菜单..." << std::endl;
	std::cout << "[GTACHEATS] DLC-佩里科岛抢劫 载具 未添加至载具菜单..." << std::endl;
	std::cout << "[GTACHEATS] DLC-洛圣都改装车夏季 载具 未添加至载具菜单..." << std::endl;
	std::cout << "[GTACHEATS] DLC-合约 载具 未添加至载具菜单..." << std::endl;
	std::cout << "[GTACHEATS] 主题配置读取，暗红主题已设置..." << std::endl;
	std::cout << "[GTACHEATS] 菜单其他设置完成..." << std::endl;
	std::cout << "[GTACHEATS] 菜单校验完成，进游戏 F4启动..." << std::endl;
	//std::cin >> input;
	//if (0 == strcmp(input, "123")) {


		main();
	//}
	
}
