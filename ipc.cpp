#include "ipc.h"

IPC::IPC(QObject *parent)
    : QObject(parent)
    , shm_cmd("slamnav_cmd")
    , shm_ui_status("slamnav_ui_status")
    , shm_status("slamnav_status")
    , shm_path("slamnav_path")
    , shm_map("slamnav_map")
    , shm_obs("slamnav_obs")
    , shm_cam0("slamnav_cam0")
    , shm_cam1("slamnav_cam1")
    , shm_cam_color0("slamnav_cam_color0")
    , shm_cam_color1("slamnav_cam_color1")
{
    // msg tick clear, check for new data
    tick = 0;

    // create or attach
    if (!shm_cmd.create(sizeof(IPC::CMD), QSharedMemory::ReadWrite) && shm_cmd.error() == QSharedMemory::AlreadyExists)
    {
        printf("attach shared memory, key: slamnav_cmd, size: %ld\n", sizeof(IPC::CMD));
        shm_cmd.attach();
    }
    else
    {
        printf("create shared memory, key: slamnav_cmd, size: %ld\n", sizeof(IPC::CMD));
    }

    if (!shm_ui_status.create(sizeof(IPC::UI_STATUS), QSharedMemory::ReadWrite) && shm_ui_status.error() == QSharedMemory::AlreadyExists)
    {
        printf("attach shared memory, key: slamnav_ui_status, size: %ld\n", sizeof(IPC::UI_STATUS));
        shm_ui_status.attach();
    }
    else
    {
        printf("create shared memory, key: slamnav_ui_status, size: %ld\n", sizeof(IPC::UI_STATUS));
    }

    if (!shm_status.create(sizeof(IPC::STATUS), QSharedMemory::ReadWrite) && shm_status.error() == QSharedMemory::AlreadyExists)
    {
        printf("attach shared memory, key: slamnav_status, size: %ld\n", sizeof(IPC::STATUS));
        shm_status.attach();
    }
    else
    {
        printf("create shared memory, key: slamnav_status, size: %ld\n", sizeof(IPC::STATUS));
    }

    if (!shm_path.create(sizeof(IPC::PATH), QSharedMemory::ReadWrite) && shm_path.error() == QSharedMemory::AlreadyExists)
    {
        printf("attach shared memory, key: slamnav_path, size: %ld\n", sizeof(IPC::PATH));
        shm_path.attach();
    }
    else
    {
        printf("create shared memory, key: slamnav_path, size: %ld\n", sizeof(IPC::PATH));
    }

    if (!shm_map.create(sizeof(IPC::MAP), QSharedMemory::ReadWrite) && shm_map.error() == QSharedMemory::AlreadyExists)
    {
        printf("attach shared memory, key: slamnav_map, size: %ld\n", sizeof(IPC::MAP));
        shm_map.attach();
    }
    else
    {
        printf("create shared memory, key: slamnav_map, size: %ld\n", sizeof(IPC::MAP));
    }

    if (!shm_obs.create(sizeof(IPC::MAP), QSharedMemory::ReadWrite) && shm_obs.error() == QSharedMemory::AlreadyExists)
    {
        printf("attach shared memory, key: slamnav_obs, size: %ld\n", sizeof(IPC::MAP));
        shm_obs.attach();
    }
    else
    {
        printf("create shared memory, key: slamnav_obs, size: %ld\n", sizeof(IPC::MAP));
    }

    if (!shm_cam0.create(sizeof(IPC::IMG), QSharedMemory::ReadWrite) && shm_cam0.error() == QSharedMemory::AlreadyExists)
    {
        printf("attach shared memory, key: slamnav_cam0, size: %ld\n", sizeof(IPC::IMG));
        shm_cam0.attach();
    }
    else
    {
        printf("create shared memory, key: slamnav_cam0, size: %ld\n", sizeof(IPC::IMG));
    }

    if (!shm_cam1.create(sizeof(IPC::IMG), QSharedMemory::ReadWrite) && shm_cam1.error() == QSharedMemory::AlreadyExists)
    {
        printf("attach shared memory, key: slamnav_cam1, size: %ld\n", sizeof(IPC::IMG));
        shm_cam1.attach();
    }
    else
    {
        printf("create shared memory, key: slamnav_cam1, size: %ld\n", sizeof(IPC::IMG));
    }

    if (!shm_cam_color0.create(sizeof(IPC::IMG_COLOR), QSharedMemory::ReadWrite) && shm_cam_color0.error() == QSharedMemory::AlreadyExists)
    {
        printf("attach shared memory, key: slamnav_cam_color0, size: %ld\n", sizeof(IPC::IMG_COLOR));
        shm_cam_color0.attach();
    }
    else
    {
        printf("create shared memory, key: slamnav_cam_color0, size: %ld\n", sizeof(IPC::IMG_COLOR));
    }

    if (!shm_cam_color1.create(sizeof(IPC::IMG_COLOR), QSharedMemory::ReadWrite) && shm_cam_color1.error() == QSharedMemory::AlreadyExists)
    {
        printf("attach shared memory, key: slamnav_cam_color1, size: %ld\n", sizeof(IPC::IMG_COLOR));
        shm_cam_color1.attach();
    }
    else
    {
        printf("create shared memory, key: slamnav_cam_color1, size: %ld\n", sizeof(IPC::IMG_COLOR));
    }
}

IPC::~IPC()
{
    if(shm_cmd.detach())
    {
        printf("detach shared memory, key: slamnav_cmd\n");
    }

    if(shm_ui_status.detach())
    {
        printf("detach shared memory, key: slamnav_ui_status\n");
    }

    if(shm_status.detach())
    {
        printf("detach shared memory, key: slamnav_status\n");
    }

    if(shm_path.detach())
    {
        printf("detach shared memory, key: slamnav_path\n");
    }

    if(shm_map.detach())
    {
        printf("detach shared memory, key: slamnav_map\n");
    }

    if(shm_obs.detach())
    {
        printf("detach shared memory, key: slamnav_obs\n");
    }

    if(shm_cam0.detach())
    {
        printf("detach shared memory, key: slamnav_cam0\n");
    }

    if(shm_cam1.detach())
    {
        printf("detach shared memory, key: slamnav_cam1\n");
    }
}

IPC::CMD IPC::get_cmd()
{
    IPC::CMD res;

    shm_cmd.lock();
    memcpy(&res, (char*)shm_cmd.constData(), sizeof(IPC::CMD));
    shm_cmd.unlock();

    return res;
}

IPC::UI_STATUS IPC::get_ui_status()
{
    IPC::UI_STATUS res;

    shm_ui_status.lock();
    memcpy(&res, (char*)shm_ui_status.constData(), sizeof(IPC::UI_STATUS));
    shm_ui_status.unlock();

    return res;
}

IPC::STATUS IPC::get_status()
{
    IPC::STATUS res;

    shm_status.lock();
    memcpy(&res, (char*)shm_status.constData(), sizeof(IPC::STATUS));
    shm_status.unlock();

    return res;
}

IPC::PATH IPC::get_path()
{
    IPC::PATH res;

    shm_path.lock();
    memcpy(&res, (char*)shm_path.constData(), sizeof(IPC::PATH));
    shm_path.unlock();

    return res;
}

IPC::MAP IPC::get_map()
{
    IPC::MAP res;

    shm_map.lock();
    memcpy(&res, (char*)shm_map.constData(), sizeof(IPC::MAP));
    shm_map.unlock();

    return res;
}

IPC::MAP IPC::get_obs()
{
    IPC::MAP res;

    shm_obs.lock();
    memcpy(&res, (char*)shm_obs.constData(), sizeof(IPC::MAP));
    shm_obs.unlock();

    return res;
}

IPC::IMG IPC::get_cam0()
{
    IPC::IMG res;

    shm_cam0.lock();
    memcpy(&res, (char*)shm_cam0.constData(), sizeof(IPC::IMG));
    shm_cam0.unlock();

    return res;
}

IPC::IMG IPC::get_cam1()
{
    IPC::IMG res;

    shm_cam1.lock();
    memcpy(&res, (char*)shm_cam1.constData(), sizeof(IPC::IMG));
    shm_cam1.unlock();

    return res;
}

void IPC::set_cmd(IPC::CMD val)
{
    shm_cmd.lock();
    val.tick = ++tick;
    memcpy((char*)shm_cmd.data(), &val, sizeof(IPC::CMD));
    shm_cmd.unlock();
}

void IPC::set_ui_status(IPC::UI_STATUS val)
{
    shm_ui_status.lock();
    val.tick = ++tick;
    memcpy((char*)shm_ui_status.data(), &val, sizeof(IPC::UI_STATUS));
    shm_ui_status.unlock();
}

void IPC::set_status(IPC::STATUS val)
{
    shm_status.lock();
    val.tick = ++tick;
    memcpy((char*)shm_status.data(), &val, sizeof(IPC::STATUS));
    shm_status.unlock();
}

void IPC::set_path(IPC::PATH val)
{
    shm_path.lock();
    val.tick = ++tick;
    memcpy((char*)shm_path.data(), &val, sizeof(IPC::PATH));
    shm_path.unlock();
}

void IPC::set_map(IPC::MAP val)
{
    shm_map.lock();
    val.tick = ++tick;
    memcpy((char*)shm_map.data(), &val, sizeof(IPC::MAP));
    shm_map.unlock();
}

void IPC::set_obs(IPC::MAP val)
{
    shm_obs.lock();
    val.tick = ++tick;
    memcpy((char*)shm_obs.data(), &val, sizeof(IPC::MAP));
    shm_obs.unlock();
}

void IPC::set_cam0(IPC::IMG val)
{
    shm_cam0.lock();
    val.tick = ++tick;
    memcpy((char*)shm_cam0.data(), &val, sizeof(IPC::IMG));
    shm_cam0.unlock();
}

void IPC::set_cam1(IPC::IMG val)
{
    shm_cam1.lock();
    val.tick = ++tick;
    memcpy((char*)shm_cam1.data(), &val, sizeof(IPC::IMG));
    shm_cam1.unlock();
}

void IPC::set_cam_color0(IPC::IMG_COLOR val)
{
    shm_cam_color0.lock();
    val.tick = ++tick;
    memcpy((char*)shm_cam_color0.data(), &val, sizeof(IPC::IMG_COLOR));
    shm_cam_color0.unlock();
}

void IPC::set_cam_color1(IPC::IMG_COLOR val)
{
    shm_cam_color1.lock();
    val.tick = ++tick;
    memcpy((char*)shm_cam_color1.data(), &val, sizeof(IPC::IMG_COLOR));
    shm_cam_color1.unlock();
}
