#pragma once
// MESSAGE PTZ_GYRO_CTRL PACKING

#define TTALINK_MSG_ID_PTZ_GYRO_CTRL 2302

TTAPACKED(
typedef struct __ttalink_ptz_gyro_ctrl_t {
 uint32_t update_time; /*<  update_time*/
 float gyro_pitch; /*<  .*/
 float gyro_roll; /*<  .*/
 float gyro_yaw; /*<  .*/
}) ttalink_ptz_gyro_ctrl_t;

#define TTALINK_MSG_ID_PTZ_GYRO_CTRL_LEN 16
#define TTALINK_MSG_ID_PTZ_GYRO_CTRL_MIN_LEN 16
#define TTALINK_MSG_ID_2302_LEN 16
#define TTALINK_MSG_ID_2302_MIN_LEN 16

#define TTALINK_MSG_ID_PTZ_GYRO_CTRL_CRC 38
#define TTALINK_MSG_ID_2302_CRC 38



#if TTALINK_COMMAND_24BIT
#define TTALINK_MESSAGE_INFO_PTZ_GYRO_CTRL { \
    2302, \
    "PTZ_GYRO_CTRL", \
    4, \
    {  { "update_time", NULL, TTALINK_TYPE_UINT32_T, 0, 0, offsetof(ttalink_ptz_gyro_ctrl_t, update_time) }, \
         { "gyro_pitch", NULL, TTALINK_TYPE_FLOAT, 0, 4, offsetof(ttalink_ptz_gyro_ctrl_t, gyro_pitch) }, \
         { "gyro_roll", NULL, TTALINK_TYPE_FLOAT, 0, 8, offsetof(ttalink_ptz_gyro_ctrl_t, gyro_roll) }, \
         { "gyro_yaw", NULL, TTALINK_TYPE_FLOAT, 0, 12, offsetof(ttalink_ptz_gyro_ctrl_t, gyro_yaw) }, \
         } \
}
#else
#define TTALINK_MESSAGE_INFO_PTZ_GYRO_CTRL { \
    "PTZ_GYRO_CTRL", \
    4, \
    {  { "update_time", NULL, TTALINK_TYPE_UINT32_T, 0, 0, offsetof(ttalink_ptz_gyro_ctrl_t, update_time) }, \
         { "gyro_pitch", NULL, TTALINK_TYPE_FLOAT, 0, 4, offsetof(ttalink_ptz_gyro_ctrl_t, gyro_pitch) }, \
         { "gyro_roll", NULL, TTALINK_TYPE_FLOAT, 0, 8, offsetof(ttalink_ptz_gyro_ctrl_t, gyro_roll) }, \
         { "gyro_yaw", NULL, TTALINK_TYPE_FLOAT, 0, 12, offsetof(ttalink_ptz_gyro_ctrl_t, gyro_yaw) }, \
         } \
}
#endif


static inline uint16_t _ttalink_ptz_gyro_ctrl_pack(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t* msg,
                               uint32_t update_time, float gyro_pitch, float gyro_roll, float gyro_yaw, bool nocrc)
{
#if TTALINK_NEED_BYTE_SWAP || !TTALINK_ALIGNED_FIELDS
    char buf[TTALINK_MSG_ID_PTZ_GYRO_CTRL_LEN];
    _tta_put_uint32_t(buf, 0, update_time);
    _tta_put_float(buf, 4, gyro_pitch);
    _tta_put_float(buf, 8, gyro_roll);
    _tta_put_float(buf, 12, gyro_yaw);

        memcpy(_TTA_PAYLOAD_NON_CONST(msg), buf, TTALINK_MSG_ID_PTZ_GYRO_CTRL_LEN);
#else
    ttalink_ptz_gyro_ctrl_t packet;
    packet.update_time = update_time;
    packet.gyro_pitch = gyro_pitch;
    packet.gyro_roll = gyro_roll;
    packet.gyro_yaw = gyro_yaw;

        memcpy(_TTA_PAYLOAD_NON_CONST(msg), &packet, TTALINK_MSG_ID_PTZ_GYRO_CTRL_LEN);
#endif

    msg->msgid = TTALINK_MSG_ID_PTZ_GYRO_CTRL;
    return ttalink_finalize_message(msg, dst_addr, src_addr, TTALINK_MSG_ID_PTZ_GYRO_CTRL_MIN_LEN, TTALINK_MSG_ID_PTZ_GYRO_CTRL_LEN, TTALINK_MSG_ID_PTZ_GYRO_CTRL_CRC, nocrc);
}

/**
 * @brief Pack a ptz_gyro_ctrl message
 * @param dst_addr 
 * @param src_addr
 * @param msg The TTAlink message to compress the data into
 *
 * @param update_time  update_time
 * @param gyro_pitch  .
 * @param gyro_roll  .
 * @param gyro_yaw  .
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t ttalink_ptz_gyro_ctrl_pack(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t* msg,
                               uint32_t update_time, float gyro_pitch, float gyro_roll, float gyro_yaw)
{
    return _ttalink_ptz_gyro_ctrl_pack(dst_addr, src_addr, msg,  update_time, gyro_pitch, gyro_roll, gyro_yaw, false);
}

/**
 * @brief Pack a ptz_gyro_ctrl message, no crc
 * @param dst_addr 
 * @param src_addr
 * @param msg The TTAlink message to compress the data into
 *
 * @param update_time  update_time
 * @param gyro_pitch  .
 * @param gyro_roll  .
 * @param gyro_yaw  .
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t ttalink_ptz_gyro_ctrl_pack_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t* msg,
                               uint32_t update_time, float gyro_pitch, float gyro_roll, float gyro_yaw)
{
    return _ttalink_ptz_gyro_ctrl_pack(dst_addr, src_addr, msg,  update_time, gyro_pitch, gyro_roll, gyro_yaw, true);
}


static inline uint16_t _ttalink_ptz_gyro_ctrl_pack_chan(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan,
                               ttalink_message_t* msg,
                                   uint32_t update_time,float gyro_pitch,float gyro_roll,float gyro_yaw, bool nocrc)
{
#if TTALINK_NEED_BYTE_SWAP || !TTALINK_ALIGNED_FIELDS
    char buf[TTALINK_MSG_ID_PTZ_GYRO_CTRL_LEN];
    _tta_put_uint32_t(buf, 0, update_time);
    _tta_put_float(buf, 4, gyro_pitch);
    _tta_put_float(buf, 8, gyro_roll);
    _tta_put_float(buf, 12, gyro_yaw);

        memcpy(_TTA_PAYLOAD_NON_CONST(msg), buf, TTALINK_MSG_ID_PTZ_GYRO_CTRL_LEN);
#else
    ttalink_ptz_gyro_ctrl_t packet;
    packet.update_time = update_time;
    packet.gyro_pitch = gyro_pitch;
    packet.gyro_roll = gyro_roll;
    packet.gyro_yaw = gyro_yaw;

        memcpy(_TTA_PAYLOAD_NON_CONST(msg), &packet, TTALINK_MSG_ID_PTZ_GYRO_CTRL_LEN);
#endif

    msg->msgid = TTALINK_MSG_ID_PTZ_GYRO_CTRL;
    return ttalink_finalize_message_chan(msg, dst_addr, src_addr, chan, TTALINK_MSG_ID_PTZ_GYRO_CTRL_MIN_LEN, TTALINK_MSG_ID_PTZ_GYRO_CTRL_LEN, TTALINK_MSG_ID_PTZ_GYRO_CTRL_CRC, nocrc);
}

/**
 * @brief Pack a ptz_gyro_ctrl message on a channel
 * @param dst_addr ID of this system
 * @param src_addr ID of this component (e.g. 200 for IMU)
 * @param chan The TTAlink channel this message will be sent over
 * @param msg The TTAlink message to compress the data into
 * @param update_time  update_time
 * @param gyro_pitch  .
 * @param gyro_roll  .
 * @param gyro_yaw  .
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t ttalink_ptz_gyro_ctrl_pack_chan(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan,
                               ttalink_message_t* msg,
                                   uint32_t update_time,float gyro_pitch,float gyro_roll,float gyro_yaw)
{
    return _ttalink_ptz_gyro_ctrl_pack_chan(dst_addr, src_addr, chan, msg,  update_time, gyro_pitch, gyro_roll, gyro_yaw, false);
}

/**
 * @brief Pack a ptz_gyro_ctrl message on a channel, no crc
 * @param dst_addr ID of this system
 * @param src_addr ID of this component (e.g. 200 for IMU)
 * @param chan The TTAlink channel this message will be sent over
 * @param msg The TTAlink message to compress the data into
 * @param update_time  update_time
 * @param gyro_pitch  .
 * @param gyro_roll  .
 * @param gyro_yaw  .
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t ttalink_ptz_gyro_ctrl_pack_chan_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan,
                               ttalink_message_t* msg,
                                   uint32_t update_time,float gyro_pitch,float gyro_roll,float gyro_yaw)
{
    return _ttalink_ptz_gyro_ctrl_pack_chan(dst_addr, src_addr, chan, msg,  update_time, gyro_pitch, gyro_roll, gyro_yaw, true);
}


static inline uint16_t _ttalink_ptz_gyro_ctrl_encode(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t* msg, const ttalink_ptz_gyro_ctrl_t* ptz_gyro_ctrl, bool nocrc)
{
    if(nocrc){
        return ttalink_ptz_gyro_ctrl_pack_nocrc(dst_addr, src_addr, msg, ptz_gyro_ctrl->update_time, ptz_gyro_ctrl->gyro_pitch, ptz_gyro_ctrl->gyro_roll, ptz_gyro_ctrl->gyro_yaw);
    }else{
        return ttalink_ptz_gyro_ctrl_pack(dst_addr, src_addr, msg, ptz_gyro_ctrl->update_time, ptz_gyro_ctrl->gyro_pitch, ptz_gyro_ctrl->gyro_roll, ptz_gyro_ctrl->gyro_yaw);
    }
    
}

/**
 * @brief Encode a ptz_gyro_ctrl struct
 *
 * @param dst_addr ID of this system
 * @param src_addr ID of this component (e.g. 200 for IMU)
 * @param msg The TTAlink message to compress the data into
 * @param ptz_gyro_ctrl C-struct to read the message contents from
 */
static inline uint16_t ttalink_ptz_gyro_ctrl_encode(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t* msg, const ttalink_ptz_gyro_ctrl_t* ptz_gyro_ctrl)
{
    return _ttalink_ptz_gyro_ctrl_encode(dst_addr, src_addr, msg, ptz_gyro_ctrl, false);
}

/**
 * @brief Encode a ptz_gyro_ctrl struct, no crc
 *
 * @param dst_addr ID of this system
 * @param src_addr ID of this component (e.g. 200 for IMU)
 * @param msg The TTAlink message to compress the data into
 * @param ptz_gyro_ctrl C-struct to read the message contents from
 */
static inline uint16_t ttalink_ptz_gyro_ctrl_encode_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t* msg, const ttalink_ptz_gyro_ctrl_t* ptz_gyro_ctrl)
{
    return _ttalink_ptz_gyro_ctrl_encode(dst_addr, src_addr, msg, ptz_gyro_ctrl, true);
}


static inline uint16_t _ttalink_ptz_gyro_ctrl_encode_chan(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, ttalink_message_t* msg, const ttalink_ptz_gyro_ctrl_t* ptz_gyro_ctrl, bool nocrc)
{
    if(nocrc){
        return ttalink_ptz_gyro_ctrl_pack_chan_nocrc(dst_addr, src_addr, chan, msg, ptz_gyro_ctrl->update_time, ptz_gyro_ctrl->gyro_pitch, ptz_gyro_ctrl->gyro_roll, ptz_gyro_ctrl->gyro_yaw);
    }else{
        return ttalink_ptz_gyro_ctrl_pack_chan(dst_addr, src_addr, chan, msg, ptz_gyro_ctrl->update_time, ptz_gyro_ctrl->gyro_pitch, ptz_gyro_ctrl->gyro_roll, ptz_gyro_ctrl->gyro_yaw);
    }
}

/**
 * @brief Encode a ptz_gyro_ctrl struct on a channel
 *
 * @param dst_addr ID of this system
 * @param src_addr ID of this component (e.g. 200 for IMU)
 * @param chan The TTAlink channel this message will be sent over
 * @param msg The TTAlink message to compress the data into
 * @param ptz_gyro_ctrl C-struct to read the message contents from
 */
static inline uint16_t ttalink_ptz_gyro_ctrl_encode_chan(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, ttalink_message_t* msg, const ttalink_ptz_gyro_ctrl_t* ptz_gyro_ctrl)
{
    return _ttalink_ptz_gyro_ctrl_encode_chan(dst_addr, src_addr, chan, msg, ptz_gyro_ctrl, false);
}

/**
 * @brief Encode a ptz_gyro_ctrl struct on a channel, no crc
 *
 * @param dst_addr ID of this system
 * @param src_addr ID of this component (e.g. 200 for IMU)
 * @param chan The TTAlink channel this message will be sent over
 * @param msg The TTAlink message to compress the data into
 * @param ptz_gyro_ctrl C-struct to read the message contents from
 */
static inline uint16_t ttalink_ptz_gyro_ctrl_encode_chan_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, ttalink_message_t* msg, const ttalink_ptz_gyro_ctrl_t* ptz_gyro_ctrl)
{
    return _ttalink_ptz_gyro_ctrl_encode_chan(dst_addr, src_addr, chan, msg, ptz_gyro_ctrl, true);
}


#ifdef TTALINK_USE_CONVENIENCE_FUNCTIONS

static inline void _ttalink_ptz_gyro_ctrl_send(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, uint32_t update_time, float gyro_pitch, float gyro_roll, float gyro_yaw, bool nocrc)
{
#if TTALINK_NEED_BYTE_SWAP || !TTALINK_ALIGNED_FIELDS
    char buf[TTALINK_MSG_ID_PTZ_GYRO_CTRL_LEN];
    _tta_put_uint32_t(buf, 0, update_time);
    _tta_put_float(buf, 4, gyro_pitch);
    _tta_put_float(buf, 8, gyro_roll);
    _tta_put_float(buf, 12, gyro_yaw);

    _tta_finalize_message_chan_send(dst_addr, src_addr, chan, TTALINK_MSG_ID_PTZ_GYRO_CTRL, buf, TTALINK_MSG_ID_PTZ_GYRO_CTRL_MIN_LEN, TTALINK_MSG_ID_PTZ_GYRO_CTRL_LEN, TTALINK_MSG_ID_PTZ_GYRO_CTRL_CRC, nocrc);
#else
    ttalink_ptz_gyro_ctrl_t packet;
    packet.update_time = update_time;
    packet.gyro_pitch = gyro_pitch;
    packet.gyro_roll = gyro_roll;
    packet.gyro_yaw = gyro_yaw;

    _tta_finalize_message_chan_send(dst_addr, src_addr, chan, TTALINK_MSG_ID_PTZ_GYRO_CTRL, (const char *)&packet, TTALINK_MSG_ID_PTZ_GYRO_CTRL_MIN_LEN, TTALINK_MSG_ID_PTZ_GYRO_CTRL_LEN, TTALINK_MSG_ID_PTZ_GYRO_CTRL_CRC, nocrc);
#endif
}

/**
 * @brief Send a ptz_gyro_ctrl message
 * @param chan TTAlink channel to send the message
 *
 * @param update_time  update_time
 * @param gyro_pitch  .
 * @param gyro_roll  .
 * @param gyro_yaw  .
 */
static inline void ttalink_ptz_gyro_ctrl_send(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, uint32_t update_time, float gyro_pitch, float gyro_roll, float gyro_yaw)
{
    _ttalink_ptz_gyro_ctrl_send(dst_addr, src_addr, chan, update_time, gyro_pitch, gyro_roll, gyro_yaw, false);
}

/**
 * @brief Send a ptz_gyro_ctrl message, no crc
 * @param chan TTAlink channel to send the message
 *
 * @param update_time  update_time
 * @param gyro_pitch  .
 * @param gyro_roll  .
 * @param gyro_yaw  .
 */
static inline void ttalink_ptz_gyro_ctrl_send_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, uint32_t update_time, float gyro_pitch, float gyro_roll, float gyro_yaw)
{
    _ttalink_ptz_gyro_ctrl_send(dst_addr, src_addr, chan, update_time, gyro_pitch, gyro_roll, gyro_yaw, true);
}


static inline void _ttalink_ptz_gyro_ctrl_send_struct(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, const ttalink_ptz_gyro_ctrl_t* ptz_gyro_ctrl, bool nocrc)
{
#if TTALINK_NEED_BYTE_SWAP || !TTALINK_ALIGNED_FIELDS
    if(nocrc){
        ttalink_ptz_gyro_ctrl_send_nocrc(dst_addr, src_addr, chan, ptz_gyro_ctrl->update_time, ptz_gyro_ctrl->gyro_pitch, ptz_gyro_ctrl->gyro_roll, ptz_gyro_ctrl->gyro_yaw);
    }else{
        ttalink_ptz_gyro_ctrl_send(dst_addr, src_addr, chan, ptz_gyro_ctrl->update_time, ptz_gyro_ctrl->gyro_pitch, ptz_gyro_ctrl->gyro_roll, ptz_gyro_ctrl->gyro_yaw);
    }
#else
    _tta_finalize_message_chan_send(dst_addr, src_addr, chan, TTALINK_MSG_ID_PTZ_GYRO_CTRL, (const char *)ptz_gyro_ctrl, TTALINK_MSG_ID_PTZ_GYRO_CTRL_MIN_LEN, TTALINK_MSG_ID_PTZ_GYRO_CTRL_LEN, TTALINK_MSG_ID_PTZ_GYRO_CTRL_CRC, nocrc);
#endif
}

/**
 * @brief Send a ptz_gyro_ctrl message
 * @param chan TTAlink channel to send the message
 * @param struct The TTAlink struct to serialize
 */
static inline void ttalink_ptz_gyro_ctrl_send_struct(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, const ttalink_ptz_gyro_ctrl_t* ptz_gyro_ctrl)
{
    _ttalink_ptz_gyro_ctrl_send_struct(dst_addr, src_addr, chan, ptz_gyro_ctrl, false);
}

/**
 * @brief Send a ptz_gyro_ctrl message, no crc
 * @param chan TTAlink channel to send the message
 * @param struct The TTAlink struct to serialize
 */
static inline void ttalink_ptz_gyro_ctrl_send_struct_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, const ttalink_ptz_gyro_ctrl_t* ptz_gyro_ctrl)
{
    _ttalink_ptz_gyro_ctrl_send_struct(dst_addr, src_addr, chan, ptz_gyro_ctrl, true);
}

#if TTALINK_MSG_ID_PTZ_GYRO_CTRL_LEN <= TTALINK_MAX_PAYLOAD_LEN
static inline void _ttalink_ptz_gyro_ctrl_send_buf(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t *msgbuf, ttalink_channel_t chan,  uint32_t update_time, float gyro_pitch, float gyro_roll, float gyro_yaw, bool nocrc)
{
#if TTALINK_NEED_BYTE_SWAP || !TTALINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _tta_put_uint32_t(buf, 0, update_time);
    _tta_put_float(buf, 4, gyro_pitch);
    _tta_put_float(buf, 8, gyro_roll);
    _tta_put_float(buf, 12, gyro_yaw);

    _tta_finalize_message_chan_send(dst_addr, src_addr, chan, TTALINK_MSG_ID_PTZ_GYRO_CTRL, buf, TTALINK_MSG_ID_PTZ_GYRO_CTRL_MIN_LEN, TTALINK_MSG_ID_PTZ_GYRO_CTRL_LEN, TTALINK_MSG_ID_PTZ_GYRO_CTRL_CRC, nocrc);
#else
    ttalink_ptz_gyro_ctrl_t *packet = (ttalink_ptz_gyro_ctrl_t *)msgbuf;
    packet->update_time = update_time;
    packet->gyro_pitch = gyro_pitch;
    packet->gyro_roll = gyro_roll;
    packet->gyro_yaw = gyro_yaw;

    _tta_finalize_message_chan_send(dst_addr, src_addr, chan, TTALINK_MSG_ID_PTZ_GYRO_CTRL, (const char *)packet, TTALINK_MSG_ID_PTZ_GYRO_CTRL_MIN_LEN, TTALINK_MSG_ID_PTZ_GYRO_CTRL_LEN, TTALINK_MSG_ID_PTZ_GYRO_CTRL_CRC, nocrc);
#endif
}

/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  ttalink_message_t which is the size of a full ttalink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void ttalink_ptz_gyro_ctrl_send_buf(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t *msgbuf, ttalink_channel_t chan,  uint32_t update_time, float gyro_pitch, float gyro_roll, float gyro_yaw)
{
    _ttalink_ptz_gyro_ctrl_send_buf(dst_addr, src_addr, msgbuf, chan, update_time, gyro_pitch, gyro_roll, gyro_yaw, false);
}

/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  ttalink_message_t which is the size of a full ttalink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage, no crc.
 */
static inline void ttalink_ptz_gyro_ctrl_send_buf_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t *msgbuf, ttalink_channel_t chan,  uint32_t update_time, float gyro_pitch, float gyro_roll, float gyro_yaw)
{
    _ttalink_ptz_gyro_ctrl_send_buf(dst_addr, src_addr, msgbuf, chan, update_time, gyro_pitch, gyro_roll, gyro_yaw, true);
}
#endif

#endif

// MESSAGE PTZ_GYRO_CTRL UNPACKING


/**
 * @brief Get field update_time from ptz_gyro_ctrl message
 *
 * @return  update_time
 */
static inline uint32_t ttalink_ptz_gyro_ctrl_get_update_time(const ttalink_message_t* msg)
{
    return _TTA_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field gyro_pitch from ptz_gyro_ctrl message
 *
 * @return  .
 */
static inline float ttalink_ptz_gyro_ctrl_get_gyro_pitch(const ttalink_message_t* msg)
{
    return _TTA_RETURN_float(msg,  4);
}

/**
 * @brief Get field gyro_roll from ptz_gyro_ctrl message
 *
 * @return  .
 */
static inline float ttalink_ptz_gyro_ctrl_get_gyro_roll(const ttalink_message_t* msg)
{
    return _TTA_RETURN_float(msg,  8);
}

/**
 * @brief Get field gyro_yaw from ptz_gyro_ctrl message
 *
 * @return  .
 */
static inline float ttalink_ptz_gyro_ctrl_get_gyro_yaw(const ttalink_message_t* msg)
{
    return _TTA_RETURN_float(msg,  12);
}

/**
 * @brief Decode a ptz_gyro_ctrl message into a struct
 *
 * @param msg The message to decode
 * @param ptz_gyro_ctrl C-struct to decode the message contents into
 */
static inline void ttalink_ptz_gyro_ctrl_decode(const ttalink_message_t* msg, ttalink_ptz_gyro_ctrl_t* ptz_gyro_ctrl)
{
#if TTALINK_NEED_BYTE_SWAP || !TTALINK_ALIGNED_FIELDS
    ptz_gyro_ctrl->update_time = ttalink_ptz_gyro_ctrl_get_update_time(msg);
    ptz_gyro_ctrl->gyro_pitch = ttalink_ptz_gyro_ctrl_get_gyro_pitch(msg);
    ptz_gyro_ctrl->gyro_roll = ttalink_ptz_gyro_ctrl_get_gyro_roll(msg);
    ptz_gyro_ctrl->gyro_yaw = ttalink_ptz_gyro_ctrl_get_gyro_yaw(msg);
#else
        uint8_t len = msg->len < TTALINK_MSG_ID_PTZ_GYRO_CTRL_LEN? msg->len : TTALINK_MSG_ID_PTZ_GYRO_CTRL_LEN;
        memset(ptz_gyro_ctrl, 0, TTALINK_MSG_ID_PTZ_GYRO_CTRL_LEN);
    memcpy(ptz_gyro_ctrl, _TTA_PAYLOAD(msg), len);
#endif
}
