#include "./SceneManager/scene.h"
#include "./SceneManager/menuscene.h"
#include "./SceneManager/gamescene.h"
#include "./SceneManager/choosingscene.h"
#include "./SceneManager/scenemanager.h"
#include "./graphics/atlas.h"
#include "util.h"
#include <QApplication>

QImage img_menu_backgroud;                      //主菜单背景图片
QImage img_vs;;                                 //VS艺术字图片
QImage img_1P;                                  //1P文本图片
QImage img_2P;                                  //2P文本图片
QImage img_1P_desc;                             //1P键位描述图片
QImage img_2P_desc;                             //2P键位描述图片
QImage img_gravestone_left;                     //朝向左的墓碑图片
QImage img_gravestone_right;
QImage img_selector_tip;                        //选角界面提示信息文本图片
QImage img_selector_background;                 //选角界面背景图
QImage img_1P_selector_btn_idle_left;           //1P向左选择按钮默认状态图片
QImage img_1P_selector_btn_idle_right;
QImage img_1P_selector_btn_down_left;           //1P向左选择按钮按下状态图片
QImage img_1P_selector_btn_down_right;
QImage img_2P_selector_btn_idle_left;           //2P向左选择按钮默认状态图片
QImage img_2P_selector_btn_idle_right;
QImage img_2P_selector_btn_down_left;           //2P向左选择按钮按下状态图片
QImage img_2P_selector_btn_down_right;
QImage img_peashooter_selector_background_left; //选角界面朝向左的豌豆射手背景图片
QImage img_peashooter_selector_background_right;
QImage img_sunflower_selector_background_left;  //选角界面朝向左的向日葵背景图片
QImage img_sunflower_selector_background_right;

QImage img_sky;                                 //天空图片
QImage img_hills;                               //山脉图片
QImage img_platform_large;                      //大型平台图片
QImage img_platform_small;                      //小型平台图片

QImage img_1P_cursor;                           //1P指示光标图片
QImage img_2P_cursor;

Atlas atlas_peashooter_idle_left;               //豌豆射手朝向左的默认动画图集
Atlas atlas_peashooter_idle_right;
Atlas atlas_peashooter_run_left;                //豌豆射手朝向左的奔跑动画图集
Atlas atlas_peashooter_run_right;
Atlas atlas_peashooter_attack_ex_left;          //豌豆射手朝向左的特殊攻击动画图集
Atlas atlas_peashooter_attack_ex_right;
Atlas atlas_peashooter_die_left;                //豌豆射手朝向左的死亡动画图集
Atlas atlas_peashooter_die_right;

Atlas atlas_sunflower_idle_left;                //向日葵朝向左的默认动画图集
Atlas atlas_sunflower_idle_right;
Atlas atlas_sunflower_run_left;                 //向日葵朝向左的奔跑动画图集
Atlas atlas_sunflower_run_right;
Atlas atlas_sunflower_attack_ex_left;           //向日葵朝向左的特殊攻击动画图集
Atlas atlas_sunflower_attack_ex_right;
Atlas atlas_sunflower_die_left;                 //向日葵朝向左的死亡动画图集
Atlas atlas_sunflower_die_right;

QImage img_pea;                                 //豌豆图片
Atlas atlas_pea_break;                          //豌豆破碎动画图集
Atlas atlas_sun;                                //日光动画图集
Atlas atlas_sun_explode;                        //日光爆炸动画图集
Atlas atlas_sun_ex;                             //特殊日光动画图集
Atlas atlas_sun_ex_explode;                    //特殊日光爆炸动画图集
Atlas atlas_sun_text;                           //“日”文本动画图集

Atlas atlas_run_effect;                         //奔跑特效动画图集
Atlas atlas_jump_effect;                        //跳跃特效动画图集
Atlas atlas_land_effect;                        //落地特效动画图集

QImage img_1P_winner;                           //1P获胜文本图片
QImage img_2P_winner;
QImage img_winner_bar;                          //获胜玩家文本背景图片

QImage img_avatar_peashooter;                   //豌豆射手头像图片
QImage img_avatar_sunflower;                    //向日葵头像图片


Scene* menu_scene = nullptr;        //注意此处是Scene而非MenuScene
Scene* game_scene = nullptr;
Scene* choosing_scene = nullptr;
SceneManager* scene_manager = nullptr;

void load_game_resources();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    load_game_resources();

    scene_manager = new SceneManager();
    menu_scene = new MenuScene();
    game_scene = new GameScene();
    choosing_scene = new ChoosingScene();

    scene_manager->set_current_scene(menu_scene);
    scene_manager->show();

    return a.exec();
}

void load_game_resources()
{
    img_menu_backgroud.load(":/static/resources/menu_background.png");

    img_vs.load(":/static/resources/VS.png");
    img_1P.load(":/static/resources/1P.png");
    img_2P.load(":/static/resources/2P.png");
    img_1P_desc.load(":/static/resources/1P_desc.png");
    img_2P_desc.load(":/static/resources/2P_desc.png");
    img_gravestone_right.load(":/static/resources/gravestone.png");
    flip_img(img_gravestone_left, img_gravestone_right);
    img_selector_tip.load(":/static/resources/selector_tip.png");
    img_selector_background.load(":/static/resources/selector_background.png");
    img_1P_selector_btn_idle_right.load(":/static/resources/1P_selector_btn_idle.png");
    flip_img(img_1P_selector_btn_idle_left, img_1P_selector_btn_idle_right);
    img_1P_selector_btn_down_right.load(":/static/resources/1P_selector_btn_down.png");
    flip_img(img_1P_selector_btn_down_left, img_1P_selector_btn_down_right);
    img_peashooter_selector_background_right.load(":/static/resources/peashooter_selector_background.png");
    flip_img(img_peashooter_selector_background_left, img_peashooter_selector_background_right);
    img_sunflower_selector_background_right.load(":/static/resources/sunflower_selector_background.png");
    flip_img(img_sunflower_selector_background_left, img_sunflower_selector_background_right);

    img_sky.load(":/static/resources/sky.png");
    img_hills.load(":/static/resources/hills.png");
    img_platform_large.load(":/static/resources/platform_large.png");
    img_platform_small.load(":/static/resources/platform_small.png");

    img_1P_cursor.load(":/static/resources/1P_cursor.png");
    img_2P_cursor.load(":/static/resources/2P_cursor.png");

    atlas_peashooter_idle_right.load_from_file(":/Plants/PeaShooter/resources/peashooter_idle_",9);
    flip_atlas(atlas_peashooter_idle_left, atlas_peashooter_idle_right);
    atlas_peashooter_run_right.load_from_file(":/Plants/PeaShooter/resources/peashooter_run_",5);
    flip_atlas(atlas_peashooter_run_left, atlas_peashooter_run_right);
    atlas_peashooter_attack_ex_right.load_from_file(":/Plants/PeaShooter/resources/peashooter_attack_ex_",3);
    flip_atlas(atlas_peashooter_attack_ex_left, atlas_peashooter_die_right);
    atlas_peashooter_die_right.load_from_file(":/Plants/PeaShooter/resources/peashooter_die_",4);
    flip_atlas(atlas_peashooter_die_left, atlas_peashooter_die_right);

    atlas_sunflower_idle_right.load_from_file(":/Plants/Sunflower/resources/sunflower_idle_",8);
    flip_atlas(atlas_sunflower_idle_left, atlas_sunflower_idle_right);
    atlas_sunflower_run_right.load_from_file(":/Plants/Sunflower/resources/sunflower_run_",5);
    flip_atlas(atlas_sunflower_run_left, atlas_sunflower_run_right);
    atlas_sunflower_attack_ex_right.load_from_file(":/Plants/Sunflower/resources/sunflower_attack_ex_",9);
    flip_atlas(atlas_sunflower_attack_ex_left, atlas_sunflower_attack_ex_right);
    atlas_sunflower_die_right.load_from_file(":/Plants/Sunflower/resources/sunflower_die_",2);
    flip_atlas(atlas_sunflower_die_left, atlas_sunflower_die_right);

    img_pea.load(":/static/resources/pea.png");
    atlas_pea_break.load_from_file(":/Plants/PeaShooter/resources/pea_break_",3);
    atlas_sun.load_from_file(":/Plants/Sunflower/resources/sun_", 5);
    atlas_sun_explode.load_from_file(":/Plants/Sunflower/resources/sun_explode_", 5);
    atlas_sun_ex.load_from_file(":/Plants/Sunflower/resources/sun_ex_", 5);
    atlas_sun_ex_explode.load_from_file(":/Plants/Sunflower/resources/sun_ex_explode_",5);
    atlas_sun_text.load_from_file(":/Plants/Sunflower/resources/sun_text_", 6);

    atlas_run_effect.load_from_file(":/Plants/Util/resources/run_effect_", 4);
    atlas_jump_effect.load_from_file(":/Plants/Util/resources/jump_effect_", 5);
    atlas_land_effect.load_from_file(":/Plants/Util/resources/land_effect_", 2);

    img_1P_winner.load(":/static/resources/1P_winner.png");
    img_2P_winner.load(":/static/resources/2P_winner.png");
    img_winner_bar.load(":/static/resources/winner_bar.png");
    img_avatar_peashooter.load(":/static/resources/avatar_peashooter.png");
    img_avatar_sunflower.load(":/static/resources/avatar_peashooter.png");

    //音乐资源加载





}
