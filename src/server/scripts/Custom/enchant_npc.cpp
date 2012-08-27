#include "ScriptPCH.h"

class enchant_npc : public CreatureScript {
public: enchant_npc() : CreatureScript("enchant_npc") {}

bool OnGossipHello(Player *player, Creature * creature) {
	MainMenu(player, creature);
    return true; }

void MainMenu(Player *player, Creature *creature) {
        player->ADD_GOSSIP_ITEM(0, "Dos", GOSSIP_SENDER_MAIN, 14);
        player->ADD_GOSSIP_ITEM(0, "Torse", GOSSIP_SENDER_MAIN, 4);
        player->ADD_GOSSIP_ITEM(0, "Poignets", GOSSIP_SENDER_MAIN, 8);
        player->ADD_GOSSIP_ITEM(0, "Mains", GOSSIP_SENDER_MAIN, 9);
        Item *item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, 6); if(item)
        player->ADD_GOSSIP_ITEM(0, "Jambes : Renfort d'armure épais", GOSSIP_SENDER_MAIN, 6);
        player->ADD_GOSSIP_ITEM(0, "Pieds", GOSSIP_SENDER_MAIN, 7);
        player->ADD_GOSSIP_ITEM(0, "Main droite", GOSSIP_SENDER_MAIN, 15);		
        item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, 16); if(item) {
		if(item->GetTemplate()->SubClass == 6)	player->ADD_GOSSIP_ITEM(0, "Bouclier", GOSSIP_SENDER_MAIN, 18);
        else { if(item->GetTemplate()->Class != 4) player->ADD_GOSSIP_ITEM(0, "Main gauche", GOSSIP_SENDER_MAIN, 16); } }
        item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, 17); if(item) {
		if((item->GetTemplate()->SubClass == 2) || (item->GetTemplate()->SubClass == 3) || (item->GetTemplate()->SubClass == 18))
			player->ADD_GOSSIP_ITEM(0, "A distance : lunette mortelle", GOSSIP_SENDER_MAIN, 17); }
		player->SEND_GOSSIP_MENU(20003, creature->GetGUID()); }

void Ench(Player *player, Creature *creature) {
	Item *item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, player->GetClmSlotId());
	
	if(!item) {
		creature->MonsterWhisper("Vous devez vous équiper de l'objet.", player->GetGUID());
		MainMenu(player, creature);
        return; }
    if (player->GetClmReqIl() == 1 && item->GetTemplate()->ItemLevel <= 34) {
		creature->MonsterWhisper("L'objet n'est pas d'un niveau suffisant.", player->GetGUID());
		MainMenu(player, creature);
        return; }
    if (player->GetClmTwoHa() == 1 && item->GetTemplate()->InventoryType != 17) {
		creature->MonsterWhisper("Cette enchantement requiert une arme à deux mains.", player->GetGUID());
		MainMenu(player, creature);
        return; }
	if (player->GetClmSlotId() == 16) {
	if ((item->GetTemplate()->Class == 4) && (item->GetTemplate()->SubClass != 6)) {
		creature->MonsterWhisper("Je n'enchante pas ce genre d'objets.", player->GetGUID());
		player->CLOSE_GOSSIP_MENU();
        return; }
	if(item->GetTemplate()->SubClass == 6 && player->GetClmSlty() == 1) {
		creature->MonsterWhisper("Un enchantement d'arme ne va pas sur un bouclier.", player->GetGUID());
		player->CLOSE_GOSSIP_MENU();
		return; }
	if(item->GetTemplate()->SubClass != 6 && player->GetClmSlty() == 0) {
		creature->MonsterWhisper("Un enchantement de bouclier ne va pas sur ce type d'arme.", player->GetGUID());
		player->CLOSE_GOSSIP_MENU();
		return; } }
	SpellItemEnchantmentEntry const* enchant_id = sSpellItemEnchantmentStore.LookupEntry(player->GetClmEnchId());
	if (!enchant_id) {
		creature->MonsterWhisper("L'enchantement sélectionné n'est pas un enchantement, prévenez un administrateur.", player->GetGUID());
		player->CLOSE_GOSSIP_MENU();
        return; }
	player->ApplyEnchantment(item, PERM_ENCHANTMENT_SLOT, false);
	item->SetEnchantment(PERM_ENCHANTMENT_SLOT, player->GetClmEnchId(), 0, 0);
	player->ApplyEnchantment(item, PERM_ENCHANTMENT_SLOT, true);
	/*else {
	player->ADD_GOSSIP_ITEM(0, "<Retour>", GOSSIP_SENDER_MAIN, 100);
	player->SEND_GOSSIP_MENU(1000011, creature->GetGUID()); 
	return; }*/
	MainMenu(player, creature); }

bool OnGossipSelect(Player *player, Creature * creature, uint32 sender, uint32 action) {
    player->PlayerTalkClass->ClearMenus();

		switch (action) {
	
	case 100:	MainMenu(player, creature);	break;

// Dos
	case 14:
		player->SetClmEnchId(14);
		player->ADD_GOSSIP_ITEM(3, "70 armure", GOSSIP_SENDER_MAIN, 1412);
		player->ADD_GOSSIP_ITEM(3, "120 armure", GOSSIP_SENDER_MAIN, 1407);
		player->ADD_GOSSIP_ITEM(3, "5 résistances", GOSSIP_SENDER_MAIN, 1413);
		player->ADD_GOSSIP_ITEM(3, "7 résistances", GOSSIP_SENDER_MAIN, 1408);
		player->ADD_GOSSIP_ITEM(3, "12 agilité", GOSSIP_SENDER_MAIN, 1401);
		player->ADD_GOSSIP_ITEM(3, "12 esquive", GOSSIP_SENDER_MAIN, 1406);
		player->ADD_GOSSIP_ITEM(3, "12 défense", GOSSIP_SENDER_MAIN, 1411);
		player->ADD_GOSSIP_ITEM(3, "20 pénétration des sorts", GOSSIP_SENDER_MAIN, 1409);
		player->ADD_GOSSIP_ITEM(3, "10 résistance ombre", GOSSIP_SENDER_MAIN, 1404);
		player->ADD_GOSSIP_ITEM(3, "15 résistance ombre", GOSSIP_SENDER_MAIN, 1403);
		player->ADD_GOSSIP_ITEM(3, "15 résistance feu", GOSSIP_SENDER_MAIN, 1405);
		player->ADD_GOSSIP_ITEM(3, "15 résistance arcane", GOSSIP_SENDER_MAIN, 1410);
		player->ADD_GOSSIP_ITEM(3, "15 résistance nature", GOSSIP_SENDER_MAIN, 1400);
		player->ADD_GOSSIP_ITEM(3, "camouflage", GOSSIP_SENDER_MAIN, 1402);
		player->ADD_GOSSIP_ITEM(0, "=> Retour", GOSSIP_SENDER_MAIN, 100);
		player->SEND_GOSSIP_MENU(20004, creature->GetGUID());
		break;
	case 1400:	player->SetClmEnchId(1395);							Ench(player, creature);	break;
	case 1401:	player->SetClmEnchId(368);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 1402:	player->SetClmEnchId(910);							Ench(player, creature);	break;
	case 1403:	player->SetClmEnchId(1441);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 1404:	player->SetClmEnchId(804);							Ench(player, creature);	break;
	case 1405:	player->SetClmEnchId(1349);							Ench(player, creature);	break;
	case 1406:	player->SetClmEnchId(2078);							Ench(player, creature);	break;
	case 1407:	player->SetClmEnchId(2662);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 1408:	player->SetClmEnchId(2663);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 1409:	player->SetClmEnchId(2780);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 1410:	player->SetClmEnchId(1257);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 1411:	player->SetClmEnchId(1943);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 1412:	player->SetClmEnchId(1889);							Ench(player, creature);	break;
	case 1413:	player->SetClmEnchId(1888);							Ench(player, creature);	break;
		
// Torse
	case 4:
		player->SetClmSlotId(4);
		player->ADD_GOSSIP_ITEM(3, "100 vie", GOSSIP_SENDER_MAIN, 402);
		player->ADD_GOSSIP_ITEM(3, "100 mana", GOSSIP_SENDER_MAIN, 403);
		player->ADD_GOSSIP_ITEM(3, "150 vie", GOSSIP_SENDER_MAIN, 401);
		player->ADD_GOSSIP_ITEM(3, "4 caracteristiques", GOSSIP_SENDER_MAIN, 404);
		player->ADD_GOSSIP_ITEM(3, "6 caracteristiques", GOSSIP_SENDER_MAIN, 400);
		player->ADD_GOSSIP_ITEM(3, "7 mana par 5 secondes", GOSSIP_SENDER_MAIN, 405);
		player->ADD_GOSSIP_ITEM(3, "15 résilience", GOSSIP_SENDER_MAIN, 406);
		player->ADD_GOSSIP_ITEM(3, "15 esprit", GOSSIP_SENDER_MAIN, 407);
		player->ADD_GOSSIP_ITEM(0, "=> Retour", GOSSIP_SENDER_MAIN, 100);
		player->SEND_GOSSIP_MENU(20005, creature->GetGUID());
		break;
	case 400:	player->SetClmEnchId(2661);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 401:	player->SetClmEnchId(2659);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 402:	player->SetClmEnchId(1892);							Ench(player, creature);	break;
	case 403:	player->SetClmEnchId(1893);							Ench(player, creature);	break;
	case 404:	player->SetClmEnchId(1891);							Ench(player, creature);	break;
	case 405:	player->SetClmEnchId(2852);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 406:	player->SetClmEnchId(2789);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 407:	player->SetClmEnchId(1144);	player->SetClmReqIl(1);	Ench(player, creature);	break;
  
// Bras
	case 8:
		player->SetClmSlotId(8);
		player->ADD_GOSSIP_ITEM(3, "12 endurance", GOSSIP_SENDER_MAIN, 805);
		player->ADD_GOSSIP_ITEM(3, "12 intelligence", GOSSIP_SENDER_MAIN, 806);
		player->ADD_GOSSIP_ITEM(3, "12 force", GOSSIP_SENDER_MAIN, 801);
		player->ADD_GOSSIP_ITEM(3, "24 puissance d'attaque", GOSSIP_SENDER_MAIN, 807);
		player->ADD_GOSSIP_ITEM(3, "15 puissance des sorts", GOSSIP_SENDER_MAIN, 800);
		player->ADD_GOSSIP_ITEM(3, "4 caracteristiques", GOSSIP_SENDER_MAIN, 802);
		player->ADD_GOSSIP_ITEM(3, "9 esprit", GOSSIP_SENDER_MAIN, 808);
		player->ADD_GOSSIP_ITEM(3, "12 défense", GOSSIP_SENDER_MAIN, 803);
		player->ADD_GOSSIP_ITEM(3, "8 mana par les 5 secondes", GOSSIP_SENDER_MAIN, 804);
		player->ADD_GOSSIP_ITEM(0, "=> Retour", GOSSIP_SENDER_MAIN, 100);
		player->SEND_GOSSIP_MENU(20006, creature->GetGUID());
		break;
	case 800:	player->SetClmEnchId(2319);							Ench(player, creature);	break;
	case 801:	player->SetClmEnchId(372);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 802:	player->SetClmEnchId(1891);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 803:	player->SetClmEnchId(1943);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 804:	player->SetClmEnchId(2382);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 805:	player->SetClmEnchId(371);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 806:	player->SetClmEnchId(369);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 807:	player->SetClmEnchId(1593);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 808:	player->SetClmEnchId(355);							Ench(player, creature);	break;

// Mains
	case 9:
		player->SetClmSlotId(9);
		player->ADD_GOSSIP_ITEM(3, "15 force", GOSSIP_SENDER_MAIN, 904);
		player->ADD_GOSSIP_ITEM(3, "15 agilité", GOSSIP_SENDER_MAIN, 901);
		player->ADD_GOSSIP_ITEM(3, "15 toucher", GOSSIP_SENDER_MAIN, 903);
		player->ADD_GOSSIP_ITEM(3, "10 critique", GOSSIP_SENDER_MAIN, 902);
		player->ADD_GOSSIP_ITEM(3, "26 puissance d'attaque", GOSSIP_SENDER_MAIN, 905);
		player->ADD_GOSSIP_ITEM(3, "20 puissance des sorts", GOSSIP_SENDER_MAIN, 906);
		player->ADD_GOSSIP_ITEM(3, "10 hâte", GOSSIP_SENDER_MAIN, 907);
		player->ADD_GOSSIP_ITEM(3, "2% vitesse monture", GOSSIP_SENDER_MAIN, 908);
		player->ADD_GOSSIP_ITEM(3, "5 pêche", GOSSIP_SENDER_MAIN, 900);
		player->ADD_GOSSIP_ITEM(0, "=> Retour", GOSSIP_SENDER_MAIN, 100);
		player->SEND_GOSSIP_MENU(20007, creature->GetGUID());
		break;
	case 900:	player->SetClmEnchId(846);							Ench(player, creature);	break;
	case 901:	player->SetClmEnchId(883);							Ench(player, creature);	break;
	case 902:	player->SetClmEnchId(2934);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 903:	player->SetClmEnchId(2935);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 904:	player->SetClmEnchId(684);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 905:	player->SetClmEnchId(1594);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 906:	player->SetClmEnchId(2323);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 907:	player->SetClmEnchId(931);							Ench(player, creature);	break;
	case 908:	player->SetClmEnchId(930);							Ench(player, creature);	break;

// Jambes
	case 6:	player->SetClmSlotId(6);	player->SetClmEnchId(18);	Ench(player, creature);	break;

// Bottes
	case 7:
		player->SetClmSlotId(7);
		player->ADD_GOSSIP_ITEM(3, "12 endurance", GOSSIP_SENDER_MAIN, 701);
		player->ADD_GOSSIP_ITEM(3, "12 agilité", GOSSIP_SENDER_MAIN, 704);
		player->ADD_GOSSIP_ITEM(3, "9 endurance + vitesse mineur", GOSSIP_SENDER_MAIN, 703);
		player->ADD_GOSSIP_ITEM(3, "6 agilité + vitesse mineur", GOSSIP_SENDER_MAIN, 705);
		player->ADD_GOSSIP_ITEM(3, "5 vie et mana par 5 secondes", GOSSIP_SENDER_MAIN, 700);
		player->ADD_GOSSIP_ITEM(3, "10 toucher et critique", GOSSIP_SENDER_MAIN, 702);
		player->ADD_GOSSIP_ITEM(3, "5 toucher", GOSSIP_SENDER_MAIN, 706);
		player->ADD_GOSSIP_ITEM(0, "=> Retour", GOSSIP_SENDER_MAIN, 100);
		player->SEND_GOSSIP_MENU(20008, creature->GetGUID());
		break;
	case 700:	player->SetClmEnchId(2656);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 701:	player->SetClmEnchId(371);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 702:	player->SetClmEnchId(2658);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 703:	player->SetClmEnchId(2940);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 704:	player->SetClmEnchId(368);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 705:	player->SetClmEnchId(2939);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 706:	player->SetClmEnchId(3858);							Ench(player, creature);	break;
		
// Armes
	case 15:	player->SetClmSlotId(15);	goto l16;	break;
	case 16:	player->SetClmSlotId(16);	l16:
	case 153:	player->SetClmSlty(1);
		player->ADD_GOSSIP_ITEM(0, "=> Page 2", GOSSIP_SENDER_MAIN, 154);
		player->ADD_GOSSIP_ITEM(3, "15 force", GOSSIP_SENDER_MAIN, 1502);
		player->ADD_GOSSIP_ITEM(3, "20 force", GOSSIP_SENDER_MAIN, 1508);
		player->ADD_GOSSIP_ITEM(3, "15 agilité", GOSSIP_SENDER_MAIN, 1503);
		player->ADD_GOSSIP_ITEM(3, "20 agilité", GOSSIP_SENDER_MAIN, 1517);
		player->ADD_GOSSIP_ITEM(3, "20 esprit", GOSSIP_SENDER_MAIN, 1504);
		player->ADD_GOSSIP_ITEM(3, "22 intelligence", GOSSIP_SENDER_MAIN, 1505);
		player->ADD_GOSSIP_ITEM(3, "30 intelligence", GOSSIP_SENDER_MAIN, 1507);
		player->ADD_GOSSIP_ITEM(3, "29 puissance des sorts", GOSSIP_SENDER_MAIN, 1516);
		player->ADD_GOSSIP_ITEM(3, "30 puissance des sorts", GOSSIP_SENDER_MAIN, 1501);
		player->ADD_GOSSIP_ITEM(3, "40 puissance des sorts (jaune)", GOSSIP_SENDER_MAIN, 1515);
		player->ADD_GOSSIP_ITEM(3, "40 puissance des sorts (blanc)", GOSSIP_SENDER_MAIN, 1509);
		player->ADD_GOSSIP_ITEM(3, "50 feu et arcanes", GOSSIP_SENDER_MAIN, 1510);
		player->ADD_GOSSIP_ITEM(3, "54 givre et ombre", GOSSIP_SENDER_MAIN, 1511);
		player->ADD_GOSSIP_ITEM(3, "5 dégâts de l'arme", GOSSIP_SENDER_MAIN, 1521);
		player->ADD_GOSSIP_ITEM(3, "7 dégâts de l'arme", GOSSIP_SENDER_MAIN, 1506);
		player->ADD_GOSSIP_ITEM(0, "=> Retour", GOSSIP_SENDER_MAIN, 100);
		player->SEND_GOSSIP_MENU(20009, creature->GetGUID());
		break;
	case 154:
		player->ADD_GOSSIP_ITEM(0, "Page 1 <=", GOSSIP_SENDER_MAIN, 153);
		player->ADD_GOSSIP_ITEM(3, "Croisé", GOSSIP_SENDER_MAIN, 1500);
		player->ADD_GOSSIP_ITEM(3, "Vol-de-vie", GOSSIP_SENDER_MAIN, 1518);
		player->ADD_GOSSIP_ITEM(3, "Impie", GOSSIP_SENDER_MAIN, 1519);
		player->ADD_GOSSIP_ITEM(3, "Flamboyante", GOSSIP_SENDER_MAIN, 1520);
		player->ADD_GOSSIP_ITEM(3, "Frisson glacial", GOSSIP_SENDER_MAIN, 1522);
		player->ADD_GOSSIP_ITEM(3, "Tueur de démons", GOSSIP_SENDER_MAIN, 1523);
		player->ADD_GOSSIP_ITEM(3, "Mangouste", GOSSIP_SENDER_MAIN, 1512);
		player->ADD_GOSSIP_ITEM(3, "Eruption de sort", GOSSIP_SENDER_MAIN, 1513);
		player->ADD_GOSSIP_ITEM(3, "Maître de guerre", GOSSIP_SENDER_MAIN, 1514);
		player->ADD_GOSSIP_ITEM(3, "2M - 25 agilité", GOSSIP_SENDER_MAIN, 1524);
		player->ADD_GOSSIP_ITEM(3, "2M - 70 puissance d'attaque", GOSSIP_SENDER_MAIN, 1525);
		player->ADD_GOSSIP_ITEM(3, "2M - 35 agilité", GOSSIP_SENDER_MAIN, 1526);
		player->ADD_GOSSIP_ITEM(3, "2M - 9 dégâts de l'arme", GOSSIP_SENDER_MAIN, 1527);
		player->ADD_GOSSIP_ITEM(0, "=> Retour", GOSSIP_SENDER_MAIN, 100);
		player->SEND_GOSSIP_MENU(20009, creature->GetGUID());
		break;
// 1M
	case 1500:	player->SetClmEnchId(1900);							Ench(player, creature);	break;
	case 1501:	player->SetClmEnchId(2504);							Ench(player, creature);	break;
	case 1502:	player->SetClmEnchId(2563);							Ench(player, creature);	break;
	case 1503:	player->SetClmEnchId(2564);							Ench(player, creature);	break;
	case 1504:	player->SetClmEnchId(2567);							Ench(player, creature);	break;
	case 1505:	player->SetClmEnchId(2568);							Ench(player, creature);	break;
	case 1506:	player->SetClmEnchId(120);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 1507:	player->SetClmEnchId(2666);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 1508:	player->SetClmEnchId(2668);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 1509:	player->SetClmEnchId(2669);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 1510:	player->SetClmEnchId(2671);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 1511:	player->SetClmEnchId(2672);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 1512:	player->SetClmEnchId(2673);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 1513:	player->SetClmEnchId(2674);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 1514:	player->SetClmEnchId(2675);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 1515:	player->SetClmEnchId(3846);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 1516:	player->SetClmEnchId(2505);							Ench(player, creature);	break;
	case 1517:	player->SetClmEnchId(3222);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 1518:	player->SetClmEnchId(1898);							Ench(player, creature);	break;
	case 1519:	player->SetClmEnchId(1899);							Ench(player, creature);	break;
	case 1520:	player->SetClmEnchId(803);							Ench(player, creature);	break;
	case 1521:	player->SetClmEnchId(118);							Ench(player, creature);	break;
	case 1522:	player->SetClmEnchId(1894);							Ench(player, creature);	break;
	case 1523:	player->SetClmEnchId(912);							Ench(player, creature);	break;
// 2M
	case 1524:	player->SetClmEnchId(2646);	player->SetClmTwoHa(1);							Ench(player, creature);	break;
	case 1525:	player->SetClmEnchId(2667);	player->SetClmTwoHa(1);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 1526:	player->SetClmEnchId(2670);	player->SetClmTwoHa(1);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 1527:	player->SetClmEnchId(1895);	player->SetClmTwoHa(1);							Ench(player, creature);	break;

// Boucliers
	case 18:
		player->SetClmSlotId(16);
		player->ADD_GOSSIP_ITEM(3, "18 endurance", GOSSIP_SENDER_MAIN, 1803);
		player->ADD_GOSSIP_ITEM(3, "12 inteligence", GOSSIP_SENDER_MAIN, 1804);
		player->ADD_GOSSIP_ITEM(3, "12 résilience", GOSSIP_SENDER_MAIN, 1800);
		player->ADD_GOSSIP_ITEM(3, "36 valeur de blacage", GOSSIP_SENDER_MAIN, 1801);
		player->ADD_GOSSIP_ITEM(3, "15 score de blocage", GOSSIP_SENDER_MAIN, 1802);
		player->ADD_GOSSIP_ITEM(3, "5 à toutes les résistances", GOSSIP_SENDER_MAIN, 1805);
		player->ADD_GOSSIP_ITEM(0, "=> Retour", GOSSIP_SENDER_MAIN, 100);
		player->SEND_GOSSIP_MENU(20010, creature->GetGUID());
		break;
	case 1800:	player->SetClmEnchId(3229);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 1801:	player->SetClmEnchId(2653);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 1802:	player->SetClmEnchId(1985);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 1803:	player->SetClmEnchId(1071);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 1804:	player->SetClmEnchId(2654);	player->SetClmReqIl(1);	Ench(player, creature);	break;
	case 1805:	player->SetClmEnchId(1888);	player->SetClmReqIl(1);	Ench(player, creature);	break;
		
// Ranged
	case 17:	player->SetClmSlotId(17);	player->SetClmEnchId(663);	Ench(player, creature);	break;
	
		}
	return true; }
};

void AddSc_enchant_npc() {
	new enchant_npc(); }