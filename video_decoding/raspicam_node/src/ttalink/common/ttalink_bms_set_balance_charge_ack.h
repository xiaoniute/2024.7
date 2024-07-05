#pragma once
// MESSAGE BMS_SET_BALANCE_CHARGE_ACK PACKING

#define TTALINK_MSG_ID_BMS_SET_BALANCE_CHARGE_ACK 2064

TTAPACKED(
typedef struct __ttalink_bms_set_balance_charge_ack_t {
 uint32_t update_time; /*<  . .*/
 uint8_t ack; /*<  . */
}) ttalink_bms_set_balance_charge_ack_t;

#define TTALINK_MSG_ID_BMS_SET_BALANCE_CHARGE_ACK_LEN 5
#define TTALINK_MSG_ID_BMS_SET_BALANCE_CHARGE_ACK_MIN_LEN 5
#define TTALINK_MSG_ID_2064_LEN 5
#define TTALINK_MSG_ID_2064_MIN_LEN 5

#define TTALINK_MSG_ID_BMS_SET_BALANCE_CHARGE_ACK_CRC 117
#define TTALINK_MSG_ID_2064_CRC 117



#if TTALINK_COMMAND_24BIT
#define TTALINK_MESSAGE_INFO_BMS_SET_BALANCE_CHARGE_ACK { \
    2064, \
    "BMS_SET_BALANCE_CHARGE_ACK", \
    2, \
    {  { "update_time", NULL, TTALINK_TYPE_UINT32_T, 0, 0, offsetof(ttalink_bms_set_balance_charge_ack_t, update_time) }, \
         { "ack", NULL, TTALINK_TYPE_UINT8_T, 0, 4, offsetof(ttalink_bms_set_balance_charge_ack_t, ack) }, \
         } \
}
#else
#define TTALINK_MESSAGE_INFO_BMS_SET_BALANCE_CHARGE_ACK { \
    "BMS_SET_BALANCE_CHARGE_ACK", \
    2, \
    {  { "update_time", NULL, TTALINK_TYPE_UINT32_T, 0, 0, offsetof(ttalink_bms_set_balance_charge_ack_t, update_time) }, \
         { "ack", NULL, TTALINK_TYPE_UINT8_T, 0, 4, offsetof(ttalink_bms_set_balance_charge_ack_t, ack) }, \
         } \
}
#endif


static inline uint16_t _ttalink_bms_set_balance_charge_ack_pack(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t* msg,
                               uint32_t update_time, uint8_t ack, bool nocrc)
{
#if TTALINK_NEED_BYTE_SWAP || !TTALINK_ALIGNED_FIELDS
    char buf[TTALINK_MSG_ID_BMS_SET_BALANCE_CHARGE_ACK_LEN];
    _tta_put_uint32_t(buf, 0, update_time);
    _tta_put_uint8_t(buf, 4, ack);

        memcpy(_TTA_PAYLOAD_NON_CONST(msg), buf, TTALINK_MSG_ID_BMS_SET_BALANCE_CHARGE_ACK_LEN);
#else
    ttalink_bms_set_balance_charge_ack_t packet;
    packet.update_time = update_time;
    packet.ack = ack;

        memcpy(_TTA_PAYLOAD_NON_CONST(msg), &packet, TTALINK_MSG_ID_BMS_SET_BALANCE_CHARGE_ACK_LEN);
#endif

    msg->msgid = TTALINK_MSG_ID_BMS_SET_BALANCE_CHARGE_ACK;
    return ttalink_finalize_message(msg, dst_addr, src_addr, TTALINK_MSG_ID_BMS_SET_BALANCE_CHARGE_ACK_MIN_LEN, TTALINK_MSG_ID_BMS_SET_BALANCE_CHARGE_ACK_LEN, TTALINK_MSG_ID_BMS_SET_BALANCE_CHARGE_ACK_CRC, nocrc);
}

/**
 * @brief Pack a bms_set_balance_charge_ack message
 * @param dst_addr 
 * @param src_addr
 * @param msg The TTAlink message to compress the data into
 *
 * @param update_time  . .
 * @param ack  . 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t ttalink_bms_set_balance_charge_ack_pack(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t* msg,
                               uint32_t update_time, uint8_t ack)
{
    return _ttalink_bms_set_balance_charge_ack_pack(dst_addr, src_addr, msg,  update_time, ack, false);
}

/**
 * @brief Pack a bms_set_balance_charge_ack message, no crc
 * @param dst_addr 
 * @param src_addr
 * @param msg The TTAlink message to compress the data into
 *
 * @param update_time  . .
 * @param ack  . 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t ttalink_bms_set_balance_charge_ack_pack_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t* msg,
                               uint32_t update_time, uint8_t ack)
{
    return _ttalink_bms_set_balance_charge_ack_pack(dst_addr, src_addr, msg,  update_time, ack, true);
}


static inline uint16_t _ttalink_bms_set_balance_charge_ack_pack_chan(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan,
                               ttalink_message_t* msg,
                                   uint32_t update_time,uint8_t ack, bool nocrc)
{
#if TTALINK_NEED_BYTE_SWAP || !TTALINK_ALIGNED_FIELDS
    char buf[TTALINK_MSG_ID_BMS_SET_BALANCE_CHARGE_ACK_LEN];
    _tta_put_uint32_t(buf, 0, update_time);
    _tta_put_uint8_t(buf, 4, ack);

        memcpy(_TTA_PAYLOAD_NON_CONST(msg), buf, TTALINK_MSG_ID_BMS_SET_BALANCE_CHARGE_ACK_LEN);
#else
    ttalink_bms_set_balance_charge_ack_t packet;
    packet.update_time = update_time;
    packet.ack = ack;

        memcpy(_TTA_PAYLOAD_NON_CONST(msg), &packet, TTALINK_MSG_ID_BMS_SET_BALANCE_CHARGE_ACK_LEN);
#endif

    msg->msgid = TTALINK_MSG_ID_BMS_SET_BALANCE_CHARGE_ACK;
    return ttalink_finalize_message_chan(msg, dst_addr, src_addr, chan, TTALINK_MSG_ID_BMS_SET_BALANCE_CHARGE_ACK_MIN_LEN, TTALINK_MSG_ID_BMS_SET_BALANCE_CHARGE_ACK_LEN, TTALINK_MSG_ID_BMS_SET_BALANCE_CHARGE_ACK_CRC, nocrc);
}

/**
 * @brief Pack a bms_set_balance_charge_ack message on a channel
 * @param dst_addr ID of this system
 * @param src_addr ID of this component (e.g. 200 for IMU)
 * @param chan The TTAlink channel this message will be sent over
 * @param msg The TTAlink message to compress the data into
 * @param update_time  . .
 * @param ack  . 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t ttalink_bms_set_balance_charge_ack_pack_chan(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan,
                               ttalink_message_t* msg,
                                   uint32_t update_time,uint8_t ack)
{
    return _ttalink_bms_set_balance_charge_ack_pack_chan(dst_addr, src_addr, chan, msg,  update_time, ack, false);
}

/**
 * @brief Pack a bms_set_balance_charge_ack message on a channel, no crc
 * @param dst_addr ID of this system
 * @param src_addr ID of this component (e.g. 200 for IMU)
 * @param chan The TTAlink channel this message will be sent over
 * @param msg The TTAlink message to compress the data into
 * @param update_time  . .
 * @param ack  . 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t ttalink_bms_set_balance_charge_ack_pack_chan_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan,
                               ttalink_message_t* msg,
                                   uint32_t update_time,uint8_t ack)
{
    return _ttalink_bms_set_balance_charge_ack_pack_chan(dst_addr, src_addr, chan, msg,  update_time, ack, true);
}


static inline uint16_t _ttalink_bms_set_balance_charge_ack_encode(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t* msg, const ttalink_bms_set_balance_charge_ack_t* bms_set_balance_charge_ack, bool nocrc)
{
    if(nocrc){
        return ttalink_bms_set_balance_charge_ack_pack_nocrc(dst_addr, src_addr, msg, bms_set_balance_charge_ack->update_time, bms_set_balance_charge_ack->ack);
    }else{
        return ttalink_bms_set_balance_charge_ack_pack(dst_addr, src_addr, msg, bms_set_balance_charge_ack->update_time, bms_set_balance_charge_ack->ack);
    }
    
}

/**
 * @brief Encode a bms_set_balance_charge_ack struct
 *
 * @param dst_addr ID of this system
 * @param src_addr ID of this component (e.g. 200 for IMU)
 * @param msg The TTAlink message to compress the data into
 * @param bms_set_balance_charge_ack C-struct to read the message contents from
 */
static inline uint16_t ttalink_bms_set_balance_charge_ack_encode(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t* msg, const ttalink_bms_set_balance_charge_ack_t* bms_set_balance_charge_ack)
{
    return _ttalink_bms_set_balance_charge_ack_encode(dst_addr, src_addr, msg, bms_set_balance_charge_ack, false);
}

/**
 * @brief Encode a bms_set_balance_charge_ack struct, no crc
 *
 * @param dst_addr ID of this system
 * @param src_addr ID of this component (e.g. 200 for IMU)
 * @param msg The TTAlink message to compress the data into
 * @param bms_set_balance_charge_ack C-struct to read the message contents from
 */
static inline uint16_t ttalink_bms_set_balance_charge_ack_encode_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t* msg, const ttalink_bms_set_balance_charge_ack_t* bms_set_balance_charge_ack)
{
    return _ttalink_bms_set_balance_charge_ack_encode(dst_addr, src_addr, msg, bms_set_balance_charge_ack, true);
}


static inline uint16_t _ttalink_bms_set_balance_charge_ack_encode_chan(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, ttalink_message_t* msg, const ttalink_bms_set_balance_charge_ack_t* bms_set_balance_charge_ack, bool nocrc)
{
    if(nocrc){
        return ttalink_bms_set_balance_charge_ack_pack_chan_nocrc(dst_addr, src_addr, chan, msg, bms_set_balance_charge_ack->update_time, bms_set_balance_charge_ack->ack);
    }else{
        return ttalink_bms_set_balance_charge_ack_pack_chan(dst_addr, src_addr, chan, msg, bms_set_balance_charge_ack->update_time, bms_set_balance_charge_ack->ack);
    }
}

/**
 * @brief Encode a bms_set_balance_charge_ack struct on a channel
 *
 * @param dst_addr ID of this system
 * @param src_addr ID of this component (e.g. 200 for IMU)
 * @param chan The TTAlink channel this message will be sent over
 * @param msg The TTAlink message to compress the data into
 * @param bms_set_balance_charge_ack C-struct to read the message contents from
 */
static inline uint16_t ttalink_bms_set_balance_charge_ack_encode_chan(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, ttalink_message_t* msg, const ttalink_bms_set_balance_charge_ack_t* bms_set_balance_charge_ack)
{
    return _ttalink_bms_set_balance_charge_ack_encode_chan(dst_addr, src_addr, chan, msg, bms_set_balance_charge_ack, false);
}

/**
 * @brief Encode a bms_set_balance_charge_ack struct on a channel, no crc
 *
 * @param dst_addr ID of this system
 * @param src_addr ID of this component (e.g. 200 for IMU)
 * @param chan The TTAlink channel this message will be sent over
 * @param msg The TTAlink message to compress the data into
 * @param bms_set_balance_charge_ack C-struct to read the message contents from
 */
static inline uint16_t ttalink_bms_set_balance_charge_ack_encode_chan_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, ttalink_message_t* msg, const ttalink_bms_set_balance_charge_ack_t* bms_set_balance_charge_ack)
{
    return _ttalink_bms_set_balance_charge_ack_encode_chan(dst_addr, src_addr, chan, msg, bms_set_balance_charge_ack, true);
}


#ifdef TTALINK_USE_CONVENIENCE_FUNCTIONS

static inline void _ttalink_bms_set_balance_charge_ack_send(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, uint32_t update_time, uint8_t ack, bool nocrc)
{
#if TTALINK_NEED_BYTE_SWAP || !TTALINK_ALIGNED_FIELDS
    char buf[TTALINK_MSG_ID_BMS_SET_BALANCE_CHARGE_ACK_LEN];
    _tta_put_uint32_t(buf, 0, update_time);
    _tta_put_uint8_t(buf, 4, ack);

    _tta_finalize_message_chan_send(dst_addr, src_addr, chan, TTALINK_MSG_ID_BMS_SET_BALANCE_CHARGE_ACK, buf, TTALINK_MSG_ID_BMS_SET_BALANCE_CHARGE_ACK_MIN_LEN, TTALINK_MSG_ID_BMS_SET_BALANCE_CHARGE_ACK_LEN, TTALINK_MSG_ID_BMS_SET_BALANCE_CHARGE_ACK_CRC, nocrc);
#else
    ttalink_bms_set_balance_charge_ack_t packet;
    packet.update_time = update_time;
    packet.ack = ack;

    _tta_finalize_message_chan_send(dst_addr, src_addr, chan, TTALINK_MSG_ID_BMS_SET_BALANCE_CHARGE_ACK, (const char *)&packet, TTALINK_MSG_ID_BMS_SET_BALANCE_CHARGE_ACK_MIN_LEN, TTALINK_MSG_ID_BMS_SET_BALANCE_CHARGE_ACK_LEN, TTALINK_MSG_ID_BMS_SET_BALANCE_CHARGE_ACK_CRC, nocrc);
#endif
}

/**
 * @brief Send a bms_set_balance_charge_ack message
 * @param chan TTAlink channel to send the message
 *
 * @param update_time  . .
 * @param ack  . 
 */
static inline void ttalink_bms_set_balance_charge_ack_send(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, uint32_t update_time, uint8_t ack)
{
    _ttalink_bms_set_balance_charge_ack_send(dst_addr, src_addr, chan, update_time, ack, false);
}

/**
 * @brief Send a bms_set_balance_charge_ack message, no crc
 * @param chan TTAlink channel to send the message
 *
 * @param update_time  . .
 * @param ack  . 
 */
static inline void ttalink_bms_set_balance_charge_ack_send_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, uint32_t update_time, uint8_t ack)
{
    _ttalink_bms_set_balance_charge_ack_send(dst_addr, src_addr, chan, update_time, ack, true);
}


static inline void _ttalink_bms_set_balance_charge_ack_send_struct(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, const ttalink_bms_set_balance_charge_ack_t* bms_set_balance_charge_ack, bool nocrc)
{
#if TTALINK_NEED_BYTE_SWAP || !TTALINK_ALIGNED_FIELDS
    if(nocrc){
        ttalink_bms_set_balance_charge_ack_send_nocrc(dst_addr, src_addr, chan, bms_set_balance_charge_ack->update_time, bms_set_balance_charge_ack->ack);
    }else{
        ttalink_bms_set_balance_charge_ack_send(dst_addr, src_addr, chan, bms_set_balance_charge_ack->update_time, bms_set_balance_charge_ack->ack);
    }
#else
    _tta_finalize_message_chan_send(dst_addr, src_addr, chan, TTALINK_MSG_ID_BMS_SET_BALANCE_CHARGE_ACK, (const char *)bms_set_balance_charge_ack, TTALINK_MSG_ID_BMS_SET_BALANCE_CHARGE_ACK_MIN_LEN, TTALINK_MSG_ID_BMS_SET_BALANCE_CHARGE_ACK_LEN, TTALINK_MSG_ID_BMS_SET_BALANCE_CHARGE_ACK_CRC, nocrc);
#endif
}

/**
 * @brief Send a bms_set_balance_charge_ack message
 * @param chan TTAlink channel to send the message
 * @param struct The TTAlink struct to serialize
 */
static inline void ttalink_bms_set_balance_charge_ack_send_struct(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, const ttalink_bms_set_balance_charge_ack_t* bms_set_balance_charge_ack)
{
    _ttalink_bms_set_balance_charge_ack_send_struct(dst_addr, src_addr, chan, bms_set_balance_charge_ack, false);
}

/**
 * @brief Send a bms_set_balance_charge_ack message, no crc
 * @param chan TTAlink channel to send the message
 * @param struct The TTAlink struct to serialize
 */
static inline void ttalink_bms_set_balance_charge_ack_send_struct_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, const ttalink_bms_set_balance_charge_ack_t* bms_set_balance_charge_ack)
{
    _ttalink_bms_set_balance_charge_ack_send_struct(dst_addr, src_addr, chan, bms_set_balance_charge_ack, true);
}

#if TTALINK_MSG_ID_BMS_SET_BALANCE_CHARGE_ACK_LEN <= TTALINK_MAX_PAYLOAD_LEN
static inline void _ttalink_bms_set_balance_charge_ack_send_buf(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t *msgbuf, ttalink_channel_t chan,  uint32_t update_time, uint8_t ack, bool nocrc)
{
#if TTALINK_NEED_BYTE_SWAP || !TTALINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _tta_put_uint32_t(buf, 0, update_time);
    _tta_put_uint8_t(buf, 4, ack);

    _tta_finalize_message_chan_send(dst_addr, src_addr, chan, TTALINK_MSG_ID_BMS_SET_BALANCE_CHARGE_ACK, buf, TTALINK_MSG_ID_BMS_SET_BALANCE_CHARGE_ACK_MIN_LEN, TTALINK_MSG_ID_BMS_SET_BALANCE_CHARGE_ACK_LEN, TTALINK_MSG_ID_BMS_SET_BALANCE_CHARGE_ACK_CRC, nocrc);
#else
    ttalink_bms_set_balance_charge_ack_t *packet = (ttalink_bms_set_balance_charge_ack_t *)msgbuf;
    packet->update_time = update_time;
    packet->ack = ack;

    _tta_finalize_message_chan_send(dst_addr, src_addr, chan, TTALINK_MSG_ID_BMS_SET_BALANCE_CHARGE_ACK, (const char *)packet, TTALINK_MSG_ID_BMS_SET_BALANCE_CHARGE_ACK_MIN_LEN, TTALINK_MSG_ID_BMS_SET_BALANCE_CHARGE_ACK_LEN, TTALINK_MSG_ID_BMS_SET_BALANCE_CHARGE_ACK_CRC, nocrc);
#endif
}

/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  ttalink_message_t which is the size of a full ttalink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void ttalink_bms_set_balance_charge_ack_send_buf(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t *msgbuf, ttalink_channel_t chan,  uint32_t update_time, uint8_t ack)
{
    _ttalink_bms_set_balance_charge_ack_send_buf(dst_addr, src_addr, msgbuf, chan, update_time, ack, false);
}

/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  ttalink_message_t which is the size of a full ttalink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage, no crc.
 */
static inline void ttalink_bms_set_balance_charge_ack_send_buf_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t *msgbuf, ttalink_channel_t chan,  uint32_t update_time, uint8_t ack)
{
    _ttalink_bms_set_balance_charge_ack_send_buf(dst_addr, src_addr, msgbuf, chan, update_time, ack, true);
}
#endif

#endif

// MESSAGE BMS_SET_BALANCE_CHARGE_ACK UNPACKING


/**
 * @brief Get field update_time from bms_set_balance_charge_ack message
 *
 * @return  . .
 */
static inline uint32_t ttalink_bms_set_balance_charge_ack_get_update_time(const ttalink_message_t* msg)
{
    return _TTA_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field ack from bms_set_balance_charge_ack message
 *
 * @return  . 
 */
static inline uint8_t ttalink_bms_set_balance_charge_ack_get_ack(const ttalink_message_t* msg)
{
    return _TTA_RETURN_uint8_t(msg,  4);
}

/**
 * @brief Decode a bms_set_balance_charge_ack message into a struct
 *
 * @param msg The message to decode
 * @param bms_set_balance_charge_ack C-struct to decode the message contents into
 */
static inline void ttalink_bms_set_balance_charge_ack_decode(const ttalink_message_t* msg, ttalink_bms_set_balance_charge_ack_t* bms_set_balance_charge_ack)
{
#if TTALINK_NEED_BYTE_SWAP || !TTALINK_ALIGNED_FIELDS
    bms_set_balance_charge_ack->update_time = ttalink_bms_set_balance_charge_ack_get_update_time(msg);
    bms_set_balance_charge_ack->ack = ttalink_bms_set_balance_charge_ack_get_ack(msg);
#else
        uint8_t len = msg->len < TTALINK_MSG_ID_BMS_SET_BALANCE_CHARGE_ACK_LEN? msg->len : TTALINK_MSG_ID_BMS_SET_BALANCE_CHARGE_ACK_LEN;
        memset(bms_set_balance_charge_ack, 0, TTALINK_MSG_ID_BMS_SET_BALANCE_CHARGE_ACK_LEN);
    memcpy(bms_set_balance_charge_ack, _TTA_PAYLOAD(msg), len);
#endif
}
