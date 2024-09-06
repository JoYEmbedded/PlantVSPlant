#include "gamescene.h"

GameScene::GameScene()
{

}

GameScene::~GameScene() {}

void GameScene::on_enter()
{
    music_bgm_game->play();

    pos_img_sky.setX((WINDOW_WIDTH - img_sky.width())/2);
    pos_img_sky.setY((WINDOW_HEIGHT - img_sky.height())/2);

    pos_img_hills.setX((WINDOW_WIDTH - img_hills.width())/2);
    pos_img_hills.setY((WINDOW_HEIGHT - img_hills.height())/2);

    platform_list.resize(4);

    Platform& large_platform = platform_list[0];
    large_platform.img = &img_platform_large;
    large_platform.render_position.setX(122);
    large_platform.render_position.setY(455);
    large_platform.shape.left = (float)large_platform.render_position.x() + 30;
    large_platform.shape.right = (float)large_platform.render_position.x() + large_platform.img->width() -30;
    large_platform.shape.y = (float)large_platform.render_position.y() + 60;

    Platform& small_platform_1 = platform_list[1];
    small_platform_1.img = &img_platform_small;
    small_platform_1.render_position.setX(175);
    small_platform_1.render_position.setY(360);
    small_platform_1.shape.left = (float)small_platform_1.render_position.x() + 40;
    small_platform_1.shape.right = (float)small_platform_1.render_position.x() + small_platform_1.img->width() - 40;
    small_platform_1.shape.y = (float)small_platform_1.render_position.y() + img_platform_small.height() / 2;

    Platform& small_platform_2 = platform_list[2];
    small_platform_2.img = &img_platform_small;
    small_platform_2.render_position.setX(855);
    small_platform_2.render_position.setY(360);
    small_platform_2.shape.left = (float)small_platform_2.render_position.x() + 40;
    small_platform_2.shape.right = (float)small_platform_2.render_position.x() + small_platform_2.img->width() - 40;
    small_platform_2.shape.y = (float)small_platform_2.render_position.y() + img_platform_small.height() / 2;

    Platform& small_platform_3 = platform_list[3];
    small_platform_3.img = &img_platform_small;
    small_platform_3.render_position.setX(515);
    small_platform_3.render_position.setY(225);
    small_platform_3.shape.left = (float)small_platform_3.render_position.x() + 40;
    small_platform_3.shape.right = (float)small_platform_3.render_position.x() + small_platform_3.img->width() - 40;
    small_platform_3.shape.y = (float)small_platform_3.render_position.y() + img_platform_small.height() / 2;

    player_1->set_position(200, 50);
    player_2->set_position(975, 50);

    status_bar_1P.set_avatar(img_player_1_avatar);
    status_bar_2P.set_avatar(img_player_2_avatar);
    status_bar_1P.set_position(235, 625);
    status_bar_2P.set_position(675, 625);
}

void GameScene::on_input(QKeyEvent* event, KeyType key_type)
{
    player_1->on_input(event, key_type);
    player_2->on_input(event, key_type);
}
void GameScene::on_update(int delta)
{
    player_1->on_update(delta);
    player_2->on_update(delta);
    move_and_collision(delta);
    //摄像机更新
    bullet_list.erase(std::remove_if(
        bullet_list.begin(), bullet_list.end(),
        [](const Bullet* bullet)
        {
            bool deletable = bullet->check_can_remove();
            if (deletable) delete bullet;
            return deletable;
        }),
                      bullet_list.end());

    for (Bullet* bullet : bullet_list)
        bullet->on_update(delta);

    status_bar_1P.set_HP(player_1->get_hp());
    status_bar_1P.set_MP(player_1->get_mp());
    status_bar_2P.set_HP(player_2->get_hp());
    status_bar_2P.set_MP(player_2->get_mp());
}

void GameScene::on_draw(QPainter* widget_painter, const Camera& camera)
{
    widget_painter->drawImage(pos_img_sky, img_sky);
    widget_painter->drawImage(pos_img_hills, img_hills);
    for(int i = 0; i < 4; i++)
    {
        platform_list[i].on_draw(widget_painter, camera);
    }
    player_1->on_draw(widget_painter);
    player_2->on_draw(widget_painter);

    for (Bullet* bullet : bullet_list)
        bullet->on_draw(widget_painter, camera);

    status_bar_1P.on_draw(widget_painter);
    status_bar_2P.on_draw(widget_painter);
}

void GameScene::on_exit()
{
}

void GameScene::move_and_collision(int delta)
{

    QPoint position_1P = player_1->get_position();
    QPoint position_2P = player_2->get_position();
    QVector2D velocity_1P = player_1->get_velocity();
    QVector2D velocity_2P = player_2->get_velocity();
    QVector2D shape_1P = player_1->get_shape();
    QVector2D shape_2P = player_2->get_shape();

    velocity_1P.setY(velocity_1P.y() + gravity * delta);
    position_1P.setY(position_1P.y() + velocity_1P.y() * delta);
    velocity_2P.setY(velocity_2P.y() + gravity * delta);
    position_2P.setY(position_2P.y() + velocity_2P.y() * delta);
    player_1->set_velocity(velocity_1P);
    player_1->set_position(position_1P.x(), position_1P.y());
    player_2->set_velocity(velocity_2P);
    player_2->set_position(position_2P.x(), position_2P.y());
    if (velocity_1P.y() > 0)
    {
        for(const Platform& platform : platform_list)
        {
            const Platform::CollisionShape& shape = platform.shape;
            bool is_collide_x = std::max(position_1P.x() + shape_1P.x(), shape.right) - std::min<float>(position_1P.x(), shape.left) <= shape.right - shape.left + shape_1P.x();
            bool is_collide_y = position_1P.y() < shape.y && position_1P.y() + shape_1P.y() >= shape.y;
            if(is_collide_x && is_collide_y)
            {
                float delta_pos_y = velocity_1P.y() * delta;
                float last_tick_foot_pos_y = position_1P.y() - delta_pos_y;
                if(last_tick_foot_pos_y <= shape.y)
                {
                    player_1->set_position(position_1P.x(), shape.y - shape_1P.y());
                    player_1->set_velocity(QVector2D(velocity_1P.x(), 0));
                    break;
                }
            }
        }
    }

    if (velocity_2P.y() > 0)
    {
        for(const Platform& platform : platform_list)
        {
            const Platform::CollisionShape& shape = platform.shape;
            bool is_collide_x = std::max(position_2P.x() + shape_2P.x(), shape.right) - std::min<float>(position_2P.x(), shape.left) <= shape.right - shape.left + shape_2P.x();
            bool is_collide_y = position_2P.y() < shape.y && position_2P.y() + shape_2P.y() >= shape.y;
            if(is_collide_x && is_collide_y)
            {
                float delta_pos_y = velocity_2P.y() * delta;
                float last_tick_foot_pos_y = position_2P.y() - delta_pos_y;
                if(last_tick_foot_pos_y <= shape.y)
                {
                    player_2->set_position(position_2P.x(), shape.y - shape_2P.y());
                    player_2->set_velocity(QVector2D(velocity_2P.x(), 0));
                    break;

                }
            }
        }
    }

    for (Bullet* bullet : bullet_list)
    {
        if (!bullet->get_valid())
            continue;
        if(!player_1->if_invulnerable())
        {
            if (bullet->get_collide_target() == PlayerID::P1 &&
                bullet->check_collision(QVector2D(player_1->get_position().x(), player_1->get_position().y()), QVector2D(player_1->get_shape().x(), player_1->get_shape().y())))
            {
                player_1->make_invulnerable();
                bullet->on_collide();
                bullet->set_valid(false);
                player_1->HP -= bullet->get_damage();
            }
        }
        if(!player_2->if_invulnerable())
        {
            if (bullet->get_collide_target() == PlayerID::P2 &&
                bullet->check_collision(QVector2D(player_2->get_position().x(), player_2->get_position().y()), QVector2D(player_2->get_shape().x(), player_2->get_shape().y())))
            {
                player_2->make_invulnerable();
                bullet->on_collide();
                bullet->set_valid(false);
                player_2->HP -= bullet->get_damage();
            }
        }
    }
}
