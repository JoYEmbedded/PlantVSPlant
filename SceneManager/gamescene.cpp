#include "gamescene.h"

GameScene::GameScene()
{

}

GameScene::~GameScene() {}

void GameScene::on_enter()
{
    is_game_over = false;
    is_slide_out_started = false;
    pos_img_winner_bar.setX(-img_winner_bar.width());
    pos_img_winner_bar.setY((WINDOW_HEIGHT - img_winner_bar.height()) / 2);
    pos_x_img_winner_bar_dst = (WINDOW_WIDTH - img_winner_bar.width()) / 2;

    pos_img_winner_text.setX(pos_img_winner_bar.x());
    pos_img_winner_text.setY((WINDOW_HEIGHT - img_1P_winner.height()) / 2);
    pos_x_img_winner_text_dst = (WINDOW_WIDTH - img_1P_winner.width()) / 2;

    timer_winner_slide_in.restart();
    timer_winner_slide_in.set_wait_time(2500);
    timer_winner_slide_in.set_one_shot(true);
    timer_winner_slide_in.set_callback([&]()
                                       {
                             is_slide_out_started = true;
    });

    timer_winner_slide_out.restart();
    timer_winner_slide_out.set_wait_time(1000);
    timer_winner_slide_out.set_one_shot(true);
    timer_winner_slide_out.set_callback([&]()
                                        {
                              scene_manager->switch_to(SceneManager::SceneType::Menu);
    });
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
void GameScene::on_update(int delta, Camera& camera)
{
    player_1->on_update(delta, camera);
    player_2->on_update(delta, camera);
    move_and_collision(delta);
    //摄像机更新
    camera.on_update(delta);
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
        bullet->on_update(delta, camera);

    const QPoint& position_player_1 = player_1->get_position();
    const QPoint& position_player_2 = player_2->get_position();
    if (position_player_1.y() >= WINDOW_HEIGHT)
        player_1->HP = 0;
    if (position_player_2.y() >= WINDOW_HEIGHT)
        player_2->HP = 0;
    status_bar_1P.set_HP(player_1->get_hp());
    status_bar_1P.set_MP(player_1->get_mp());
    status_bar_2P.set_HP(player_2->get_hp());
    status_bar_2P.set_MP(player_2->get_mp());

    if(player_1->get_hp() <= 0 || player_2->get_hp() <= 0)
    {
        if(!is_game_over)
        {
            music_bgm_game->stop();
            music_ui_win->play();
        }
        is_game_over = true;
    }

    if(is_game_over)
    {
        pos_img_winner_bar.setX(pos_img_winner_bar.x() + (int)(speed_winner_bar * delta));
        pos_img_winner_text.setX(pos_img_winner_text.x() + (int)(speed_winner_text * delta));
        if(!is_slide_out_started)
        {
            timer_winner_slide_in.on_update(delta);
            if(pos_img_winner_bar.x() > pos_x_img_winner_bar_dst)
                pos_img_winner_bar.setX(pos_x_img_winner_bar_dst);
            if(pos_img_winner_text.x() > pos_x_img_winner_text_dst)
                pos_img_winner_text.setX(pos_x_img_winner_text_dst);
        }
        else
            timer_winner_slide_out.on_update(delta);
    }

}

void GameScene::on_draw(QPainter* widget_painter, const Camera& camera)
{
    const QVector2D pos_camera = camera.get_position();
    widget_painter->drawImage(QPoint(pos_img_sky.x() + pos_camera.x(), pos_img_sky.y() + pos_camera.y()), img_sky);
    widget_painter->drawImage(QPoint(pos_img_hills.x() + pos_camera.x(), pos_img_hills.y() + pos_camera.y()), img_hills);
    for(int i = 0; i < 4; i++)
    {
        platform_list[i].on_draw(widget_painter, camera);
    }
    player_1->on_draw(widget_painter, camera);
    player_2->on_draw(widget_painter, camera);

    for (Bullet* bullet : bullet_list)
        bullet->on_draw(widget_painter, camera);

    if(is_game_over)
    {
        widget_painter->drawImage(QPoint(pos_img_winner_bar.x(), pos_img_winner_bar.y()), img_winner_bar);
        widget_painter->drawImage(QPoint(pos_img_winner_text.x(), pos_img_winner_text.y()), player_1->get_hp() > 0 ? img_1P_winner : img_2P_winner);
    }

    status_bar_1P.on_draw(widget_painter);
    status_bar_2P.on_draw(widget_painter);


}

void GameScene::on_exit()
{
    delete player_1;
    delete player_2;
    player_1 = nullptr;
    player_2 = nullptr;

    bullet_list.clear();
}

void GameScene::move_and_collision(int delta)
{

    QPoint position_1P = player_1->get_position();
    QPoint position_2P = player_2->get_position();
    QVector2D velocity_1P = player_1->get_velocity();
    QVector2D velocity_2P = player_2->get_velocity();
    QVector2D shape_1P = player_1->get_shape();
    QVector2D shape_2P = player_2->get_shape();
    float last_velocity_y_1P = velocity_1P.y();
    float last_velocity_y_2P = velocity_2P.y();
    velocity_1P.setY(velocity_1P.y() + gravity * delta);
    position_1P.setY(position_1P.y() + velocity_1P.y() * delta);
    velocity_2P.setY(velocity_2P.y() + gravity * delta);
    position_2P.setY(position_2P.y() + velocity_2P.y() * delta);
    player_1->set_velocity(velocity_1P);
    player_1->set_position(position_1P.x(), position_1P.y());
    player_2->set_velocity(velocity_2P);
    player_2->set_position(position_2P.x(), position_2P.y());


    if (velocity_1P.y() > 0 && player_1->HP > 0)
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
                    if(last_velocity_y_1P != 0)
                        player_1->on_land();
                    break;
                }
            }
        }
    }

    if (velocity_2P.y() > 0 && player_2->HP > 0)
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
                    if(last_velocity_y_2P != 0)
                        player_2->on_land();
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
                player_1->last_hurt_direction = bullet->get_position().x() - player_1->get_position().x();
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
                player_2->last_hurt_direction = bullet->get_position().x() - player_2->get_position().x();
            }
        }
    }
}
