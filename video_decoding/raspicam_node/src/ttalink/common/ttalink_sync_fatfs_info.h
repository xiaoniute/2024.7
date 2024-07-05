#pragma once
// MESSAGE SYNC_FATFS_INFO PACKING

#define TTALINK_MSG_ID_SYNC_FATFS_INFO 2104

TTAPACKED(
typedef struct __ttalink_sync_fatfs_info_t {
 uint32_t simple_time; /*<  . .*/
 uint8_t log_name; /*<  . .*/
 uint8_t health; /*<  . .*/
}) ttalink_sync_fatfs_info_t;

#define TTALINK_MSG_ID_SYNC_FATFS_INFO_LEN 6
#define TTALINK_MSG_ID_SYNC_FATFS_INFO_MIN_LEN 6
#define TTALINK_MSG_ID_2104_LEN 6
#define TTALINK_MSG_ID_2104_MIN_LEN 6

#define TTALINK_MSG_ID_SYNC_FATFS_INFO_CRC 189
#define TTALINK_MSG_ID_2104_CRC 189



#if TTALINK_COMMAND_24BIT
#define TTALINK_MESSAGE_INFO_SYNC_FATFS_INFO { \
    2104, \
    "SYNC_FATFS_INFO", \
    3, \
    {  { "simple_time", NULL, TTALINK_TYPE_UINT32_T, 0, 0, offsetof(ttalink_sync_fatfs_info_t, simple_time) }, \
         { "log_name", NULL, TTALINK_TYPE_UINT8_T, 0, 4, offsetof(ttalink_sync_fatfs_info_t, log_name) }, \
         { "health", NULL, TTALINK_TYPE_UINT8_T, 0, 5, offsetof(ttalink_sync_fatfs_info_t, health) }, \
         } \
}
#else
#define TTALINK_MESSAGE_INFO_SYNC_FATFS_INFO { \
    "SYNC_FATFS_INFO", \
    3, \
    {  { "simple_time", NULL, TTALINK_TYPE_UINT32_T, 0, 0, offsetof(ttalink_sync_fatfs_info_t, simple_time) }, \
         { "log_name", NULL, TTALINK_TYPE_UINT8_T, 0, 4, offsetof(ttalink_sync_fatfs_info_t, log_name) }, \
         { "health", NULL, TTALINK_TYPE_UINT8_T, 0, 5, offsetof(ttalink_sync_fatfs_info_t, health) }, \
         } \
}
#endif


static inline uint16_t _ttalink_sync_fatfs_info_pack(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t* msg,
                               uint32_t simple_time, uint8_t log_name, uint8_t health, bool nocrc)
{
#if TTALINK_NEED_BYTE_SWAP || !TTALINK_ALIGNED_FIELDS
    char buf[TTALINK_MSG_ID_SYNC_FATFS_INFO_LEN];
    _tta_put_uint32_t(buf, 0, simple_time);
    _tta_put_uint8_t(buf, 4, log_name);
    _tta_put_uint8_t(buf, 5, health);

        memcpy(_TTA_PAYLOAD_NON_CONST(msg), buf, TTALINK_MSG_ID_SYNC_FATFS_INFO_LEN);
#else
    ttalink_sync_fatfs_info_t packet;
    packet.simple_time = simple_time;
    packet.log_name = log_name;
    packet.health = health;

        memcpy(_TTA_PAYLOAD_NON_CONST(msg), &packet, TTALINK_MSG_ID_SYNC_FATFS_INFO_LEN);
#endif

    msg->msgid = TTALINK_MSG_ID_SYNC_FATFS_INFO;
    return ttalink_finalize_message(msg, dst_addr, src_addr, TTALINK_MSG_ID_SYNC_FATFS_INFO_MIN_LEN, TTALINK_MSG_ID_SYNC_FATFS_INFO_LEN, TTALINK_MSG_ID_SYNC_FATFS_INFO_CRC, nocrc);
}

/**
 * @brief Pack a sync_fatfs_info message
 * @param dst_addr 
 * @param src_addr
 * @param msg The TTAlink message to compress the data into
 *
 * @param simple_time  . .
 * @param log_name  . .
 * @param health  . .
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t ttalink_sync_fatfs_info_pack(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t* msg,
                               uint32_t simple_time, uint8_t log_name, uint8_t health)
{
    return _ttalink_sync_fatfs_info_pack(dst_addr, src_addr, msg,  simple_time, log_name, health, false);
}

/**
 * @brief Pack a sync_fatfs_info message, no crc
 * @param dst_addr 
 * @param src_addr
 * @param msg The TTAlink message to compress the data into
 *
 * @param simple_time  . .
 * @param log_name  . .
 * @param health  . .
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t ttalink_sync_fatfs_info_pack_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t* msg,
                               uint32_t simple_time, uint8_t log_name, uint8_t health)
{
    return _ttalink_sync_fatfs_info_pack(dst_addr, src_addr, msg,  simple_time, log_name, health, true);
}


static inline uint16_t _ttalink_sync_fatfs_info_pack_chan(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan,
                               ttalink_message_t* msg,
                                   uint32_t simple_time,uint8_t log_name,uint8_t health, bool nocrc)
{
#if TTALINK_NEED_BYTE_SWAP || !TTALINK_ALIGNED_FIELDS
    char buf[TTALINK_MSG_ID_SYNC_FATFS_INFO_LEN];
    _tta_put_uint32_t(buf, 0, simple_time);
    _tta_put_uint8_t(buf, 4, log_name);
    _tta_put_uint8_t(buf, 5, health);

        memcpy(_TTA_PAYLOAD_NON_CONST(msg), buf, TTALINK_MSG_ID_SYNC_FATFS_INFO_LEN);
#else
    ttalink_sync_fatfs_info_t packet;
    packet.simple_time = simple_time;
    packet.log_name = log_name;
    packet.health = health;

        memcpy(_TTA_PAYLOAD_NON_CONST(msg), &packet, TTALINK_MSG_ID_SYNC_FATFS_INFO_LEN);
#endif

    msg->msgid = TTALINK_MSG_ID_SYNC_FATFS_INFO;
    return ttalink_finalize_message_chan(msg, dst_addr, src_addr, chan, TTALINK_MSG_ID_SYNC_FATFS_INFO_MIN_LEN, TTALINK_MSG_ID_SYNC_FATFS_INFO_LEN, TTALINK_MSG_ID_SYNC_FATFS_INFO_CRC, nocrc);
}

/**
 * @brief Pack a sync_fatfs_info message on a channel
 * @param dst_addr ID of this system
 * @param src_addr ID of this component (e.g. 200 for IMU)
 * @param chan The TTAlink channel this message will be sent over
 * @param msg The TTAlink message to compress the data into
 * @param simple_time  . .
 * @param log_name  . .
 * @param health  . .
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t ttalink_sync_fatfs_info_pack_chan(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan,
                               ttalink_message_t* msg,
                                   uint32_t simple_time,uint8_t log_name,uint8_t health)
{
    return _ttalink_sync_fatfs_info_pack_chan(dst_addr, src_addr, chan, msg,  simple_time, log_name, health, false);
}

/**
 * @brief Pack a sync_fatfs_info message on a channel, no crc
 * @param dst_addr ID of this system
 * @param src_addr ID of this component (e.g. 200 for IMU)
 * @param chan The TTAlink channel this message will be sent over
 * @param msg The TTAlink message to compress the data into
 * @param simple_time  . .
 * @param log_name  . .
 * @param health  . .
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t ttalink_sync_fatfs_info_pack_chan_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan,
                               ttalink_message_t* msg,
                                   uint32_t simple_time,uint8_t log_name,uint8_t health)
{
    return _ttalink_sync_fatfs_info_pack_chan(dst_addr, src_addr, chan, msg,  simple_time, log_name, health, true);
}


static inline uint16_t _ttalink_sync_fatfs_info_encode(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t* msg, const ttalink_sync_fatfs_info_t* sync_fatfs_info, bool nocrc)
{
    if(nocrc){
        return ttalink_sync_fatfs_info_pack_nocrc(dst_addr, src_addr, msg, sync_fatfs_info->simple_time, sync_fatfs_info->log_name, sync_fatfs_info->health);
    }else{
        return ttalink_sync_fatfs_info_pack(dst_addr, src_addr, msg, sync_fatfs_info->simple_time, sync_fatfs_info->log_name, sync_fatfs_info->health);
    }
    
}

/**
 * @brief Encode a sync_fatfs_info struct
 *
 * @param dst_addr ID of this system
 * @param src_addr ID of this component (e.g. 200 for IMU)
 * @param msg The TTAlink message to compress the data into
 * @param sync_fatfs_info C-struct to read the message contents from
 */
static inline uint16_t ttalink_sync_fatfs_info_encode(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t* msg, const ttalink_sync_fatfs_info_t* sync_fatfs_info)
{
    return _ttalink_sync_fatfs_info_encode(dst_addr, src_addr, msg, sync_fatfs_info, false);
}

/**
 * @brief Encode a sync_fatfs_info struct, no crc
 *
 * @param dst_addr ID of this system
 * @param src_addr ID of this component (e.g. 200 for IMU)
 * @param msg The TTAlink message to compress the data into
 * @param sync_fatfs_info C-struct to read the message contents from
 */
static inline uint16_t ttalink_sync_fatfs_info_encode_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t* msg, const ttalink_sync_fatfs_info_t* sync_fatfs_info)
{
    return _ttalink_sync_fatfs_info_encode(dst_addr, src_addr, msg, sync_fatfs_info, true);
}


static inline uint16_t _ttalink_sync_fatfs_info_encode_chan(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, ttalink_message_t* msg, const ttalink_sync_fatfs_info_t* sync_fatfs_info, bool nocrc)
{
    if(nocrc){
        return ttalink_sync_fatfs_info_pack_chan_nocrc(dst_addr, src_addr, chan, msg, sync_fatfs_info->simple_time, sync_fatfs_info->log_name, sync_fatfs_info->health);
    }else{
        return ttalink_sync_fatfs_info_pack_chan(dst_addr, src_addr, chan, msg, sync_fatfs_info->simple_time, sync_fatfs_info->log_name, sync_fatfs_info->health);
    }
}

/**
 * @brief Encode a sync_fatfs_info struct on a channel
 *
 * @param dst_addr ID of this system
 * @param src_addr ID of this component (e.g. 200 for IMU)
 * @param chan The TTAlink channel this message will be sent over
 * @param msg The TTAlink message to compress the data into
 * @param sync_fatfs_info C-struct to read the message contents from
 */
static inline uint16_t ttalink_sync_fatfs_info_encode_chan(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, ttalink_message_t* msg, const ttalink_sync_fatfs_info_t* sync_fatfs_info)
{
    return _ttalink_sync_fatfs_info_encode_chan(dst_addr, src_addr, chan, msg, sync_fatfs_info, false);
}

/**
 * @brief Encode a sync_fatfs_info struct on a channel, no crc
 *
 * @param dst_addr ID of this system
 * @param src_addr ID of this component (e.g. 200 for IMU)
 * @param chan The TTAlink channel this message will be sent over
 * @param msg The TTAlink message to compress the data into
 * @param sync_fatfs_info C-struct to read the message contents from
 */
static inline uint16_t ttalink_sync_fatfs_info_encode_chan_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, ttalink_message_t* msg, const ttalink_sync_fatfs_info_t* sync_fatfs_info)
{
    return _ttalink_sync_fatfs_info_encode_chan(dst_addr, src_addr, chan, msg, sync_fatfs_info, true);
}


#ifdef TTALINK_USE_CONVENIENCE_FUNCTIONS

static inline void _ttalink_sync_fatfs_info_send(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, uint32_t simple_time, uint8_t log_name, uint8_t health, bool nocrc)
{
#if TTALINK_NEED_BYTE_SWAP || !TTALINK_ALIGNED_FIELDS
    char buf[TTALINK_MSG_ID_SYNC_FATFS_INFO_LEN];
    _tta_put_uint32_t(buf, 0, simple_time);
    _tta_put_uint8_t(buf, 4, log_name);
    _tta_put_uint8_t(buf, 5, health);

    _tta_finalize_message_chan_send(dst_addr, src_addr, chan, TTALINK_MSG_ID_SYNC_FATFS_INFO, buf, TTALINK_MSG_ID_SYNC_FATFS_INFO_MIN_LEN, TTALINK_MSG_ID_SYNC_FATFS_INFO_LEN, TTALINK_MSG_ID_SYNC_FATFS_INFO_CRC, nocrc);
#else
    ttalink_sync_fatfs_info_t packet;
    packet.simple_time = simple_time;
    packet.log_name = log_name;
    packet.health = health;

    _tta_finalize_message_chan_send(dst_addr, src_addr, chan, TTALINK_MSG_ID_SYNC_FATFS_INFO, (const char *)&packet, TTALINK_MSG_ID_SYNC_FATFS_INFO_MIN_LEN, TTALINK_MSG_ID_SYNC_FATFS_INFO_LEN, TTALINK_MSG_ID_SYNC_FATFS_INFO_CRC, nocrc);
#endif
}

/**
 * @brief Send a sync_fatfs_info message
 * @param chan TTAlink channel to send the message
 *
 * @param simple_time  . .
 * @param log_name  . .
 * @param health  . .
 */
static inline void ttalink_sync_fatfs_info_send(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, uint32_t simple_time, uint8_t log_name, uint8_t health)
{
    _ttalink_sync_fatfs_info_send(dst_addr, src_addr, chan, simple_time, log_name, health, false);
}

/**
 * @brief Send a sync_fatfs_info message, no crc
 * @param chan TTAlink channel to send the message
 *
 * @param simple_time  . .
 * @param log_name  . .
 * @param health  . .
 */
static inline void ttalink_sync_fatfs_info_send_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, uint32_t simple_time, uint8_t log_name, uint8_t health)
{
    _ttalink_sync_fatfs_info_send(dst_addr, src_addr, chan, simple_time, log_name, health, true);
}


static inline void _ttalink_sync_fatfs_info_send_struct(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, const ttalink_sync_fatfs_info_t* sync_fatfs_info, bool nocrc)
{
#if TTALINK_NEED_BYTE_SWAP || !TTALINK_ALIGNED_FIELDS
    if(nocrc){
        ttalink_sync_fatfs_info_send_nocrc(dst_addr, src_addr, chan, sync_fatfs_info->simple_time, sync_fatfs_info->log_name, sync_fatfs_info->health);
    }else{
        ttalink_sync_fatfs_info_send(dst_addr, src_addr, chan, sync_fatfs_info->simple_time, sync_fatfs_info->log_name, sync_fatfs_info->health);
    }
#else
    _tta_finalize_message_chan_send(dst_addr, src_addr, chan, TTALINK_MSG_ID_SYNC_FATFS_INFO, (const char *)sync_fatfs_info, TTALINK_MSG_ID_SYNC_FATFS_INFO_MIN_LEN, TTALINK_MSG_ID_SYNC_FATFS_INFO_LEN, TTALINK_MSG_ID_SYNC_FATFS_INFO_CRC, nocrc);
#endif
}

/**
 * @brief Send a sync_fatfs_info message
 * @param chan TTAlink channel to send the message
 * @param struct The TTAlink struct to serialize
 */
static inline void ttalink_sync_fatfs_info_send_struct(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, const ttalink_sync_fatfs_info_t* sync_fatfs_info)
{
    _ttalink_sync_fatfs_info_send_struct(dst_addr, src_addr, chan, sync_fatfs_info, false);
}

/**
 * @brief Send a sync_fatfs_info message, no crc
 * @param chan TTAlink channel to send the message
 * @param struct The TTAlink struct to serialize
 */
static inline void ttalink_sync_fatfs_info_send_struct_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, const ttalink_sync_fatfs_info_t* sync_fatfs_info)
{
    _ttalink_sync_fatfs_info_send_struct(dst_addr, src_addr, chan, sync_fatfs_info, true);
}

#if TTALINK_MSG_ID_SYNC_FATFS_INFO_LEN <= TTALINK_MAX_PAYLOAD_LEN
static inline void _ttalink_sync_fatfs_info_send_buf(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t *msgbuf, ttalink_channel_t chan,  uint32_t simple_time, uint8_t log_name, uint8_t health, bool nocrc)
{
#if TTALINK_NEED_BYTE_SWAP || !TTALINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _tta_put_uint32_t(buf, 0, simple_time);
    _tta_put_uint8_t(buf, 4, log_name);
    _tta_put_uint8_t(buf, 5, health);

    _tta_finalize_message_chan_send(dst_addr, src_addr, chan, TTALINK_MSG_ID_SYNC_FATFS_INFO, buf, TTALINK_MSG_ID_SYNC_FATFS_INFO_MIN_LEN, TTALINK_MSG_ID_SYNC_FATFS_INFO_LEN, TTALINK_MSG_ID_SYNC_FATFS_INFO_CRC, nocrc);
#else
    ttalink_sync_fatfs_info_t *packet = (ttalink_sync_fatfs_info_t *)msgbuf;
    packet->simple_time = simple_time;
    packet->log_name = log_name;
    packet->health = health;

    _tta_finalize_message_chan_send(dst_addr, src_addr, chan, TTALINK_MSG_ID_SYNC_FATFS_INFO, (const char *)packet, TTALINK_MSG_ID_SYNC_FATFS_INFO_MIN_LEN, TTALINK_MSG_ID_SYNC_FATFS_INFO_LEN, TTALINK_MSG_ID_SYNC_FATFS_INFO_CRC, nocrc);
#endif
}

/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  ttalink_message_t which is the size of a full ttalink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void ttalink_sync_fatfs_info_send_buf(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t *msgbuf, ttalink_channel_t chan,  uint32_t simple_time, uint8_t log_name, uint8_t health)
{
    _ttalink_sync_fatfs_info_send_buf(dst_addr, src_addr, msgbuf, chan, simple_time, log_name, health, false);
}

/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  ttalink_message_t which is the size of a full ttalink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage, no crc.
 */
static inline void ttalink_sync_fatfs_info_send_buf_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t *msgbuf, ttalink_channel_t chan,  uint32_t simple_time, uint8_t log_name, uint8_t health)
{
    _ttalink_sync_fatfs_info_send_buf(dst_addr, src_addr, msgbuf, chan, simple_time, log_name, health, true);
}
#endif

#endif

// MESSAGE SYNC_FATFS_INFO UNPACKING


/**
 * @brief Get field simple_time from sync_fatfs_info message
 *
 * @return  . .
 */
static inline uint32_t ttalink_sync_fatfs_info_get_simple_time(const ttalink_message_t* msg)
{
    return _TTA_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field log_name from sync_fatfs_info message
 *
 * @return  . .
 */
static inline uint8_t ttalink_sync_fatfs_info_get_log_name(const ttalink_message_t* msg)
{
    return _TTA_RETURN_uint8_t(msg,  4);
}

/**
 * @brief Get field health from sync_fatfs_info message
 *
 * @return  . .
 */
static inline uint8_t ttalink_sync_fatfs_info_get_health(const ttalink_message_t* msg)
{
    return _TTA_RETURN_uint8_t(msg,  5);
}

/**
 * @brief Decode a sync_fatfs_info message into a struct
 *
 * @param msg The message to decode
 * @param sync_fatfs_info C-struct to decode the message contents into
 */
static inline void ttalink_sync_fatfs_info_decode(const ttalink_message_t* msg, ttalink_sync_fatfs_info_t* sync_fatfs_info)
{
#if TTALINK_NEED_BYTE_SWAP || !TTALINK_ALIGNED_FIELDS
    sync_fatfs_info->simple_time = ttalink_sync_fatfs_info_get_simple_time(msg);
    sync_fatfs_info->log_name = ttalink_sync_fatfs_info_get_log_name(msg);
    sync_fatfs_info->health = ttalink_sync_fatfs_info_get_health(msg);
#else
        uint8_t len = msg->len < TTALINK_MSG_ID_SYNC_FATFS_INFO_LEN? msg->len : TTALINK_MSG_ID_SYNC_FATFS_INFO_LEN;
        memset(sync_fatfs_info, 0, TTALINK_MSG_ID_SYNC_FATFS_INFO_LEN);
    memcpy(sync_fatfs_info, _TTA_PAYLOAD(msg), len);
#endif
}
