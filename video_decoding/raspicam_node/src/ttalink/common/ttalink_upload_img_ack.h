#pragma once
// MESSAGE UPLOAD_IMG_ACK PACKING

#define TTALINK_MSG_ID_UPLOAD_IMG_ACK 2225

TTAPACKED(
typedef struct __ttalink_upload_img_ack_t {
 uint32_t count; /*<  .*/
 uint8_t ack; /*<  .*/
}) ttalink_upload_img_ack_t;

#define TTALINK_MSG_ID_UPLOAD_IMG_ACK_LEN 5
#define TTALINK_MSG_ID_UPLOAD_IMG_ACK_MIN_LEN 5
#define TTALINK_MSG_ID_2225_LEN 5
#define TTALINK_MSG_ID_2225_MIN_LEN 5

#define TTALINK_MSG_ID_UPLOAD_IMG_ACK_CRC 171
#define TTALINK_MSG_ID_2225_CRC 171



#if TTALINK_COMMAND_24BIT
#define TTALINK_MESSAGE_INFO_UPLOAD_IMG_ACK { \
    2225, \
    "UPLOAD_IMG_ACK", \
    2, \
    {  { "count", NULL, TTALINK_TYPE_UINT32_T, 0, 0, offsetof(ttalink_upload_img_ack_t, count) }, \
         { "ack", NULL, TTALINK_TYPE_UINT8_T, 0, 4, offsetof(ttalink_upload_img_ack_t, ack) }, \
         } \
}
#else
#define TTALINK_MESSAGE_INFO_UPLOAD_IMG_ACK { \
    "UPLOAD_IMG_ACK", \
    2, \
    {  { "count", NULL, TTALINK_TYPE_UINT32_T, 0, 0, offsetof(ttalink_upload_img_ack_t, count) }, \
         { "ack", NULL, TTALINK_TYPE_UINT8_T, 0, 4, offsetof(ttalink_upload_img_ack_t, ack) }, \
         } \
}
#endif


static inline uint16_t _ttalink_upload_img_ack_pack(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t* msg,
                               uint32_t count, uint8_t ack, bool nocrc)
{
#if TTALINK_NEED_BYTE_SWAP || !TTALINK_ALIGNED_FIELDS
    char buf[TTALINK_MSG_ID_UPLOAD_IMG_ACK_LEN];
    _tta_put_uint32_t(buf, 0, count);
    _tta_put_uint8_t(buf, 4, ack);

        memcpy(_TTA_PAYLOAD_NON_CONST(msg), buf, TTALINK_MSG_ID_UPLOAD_IMG_ACK_LEN);
#else
    ttalink_upload_img_ack_t packet;
    packet.count = count;
    packet.ack = ack;

        memcpy(_TTA_PAYLOAD_NON_CONST(msg), &packet, TTALINK_MSG_ID_UPLOAD_IMG_ACK_LEN);
#endif

    msg->msgid = TTALINK_MSG_ID_UPLOAD_IMG_ACK;
    return ttalink_finalize_message(msg, dst_addr, src_addr, TTALINK_MSG_ID_UPLOAD_IMG_ACK_MIN_LEN, TTALINK_MSG_ID_UPLOAD_IMG_ACK_LEN, TTALINK_MSG_ID_UPLOAD_IMG_ACK_CRC, nocrc);
}

/**
 * @brief Pack a upload_img_ack message
 * @param dst_addr 
 * @param src_addr
 * @param msg The TTAlink message to compress the data into
 *
 * @param count  .
 * @param ack  .
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t ttalink_upload_img_ack_pack(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t* msg,
                               uint32_t count, uint8_t ack)
{
    return _ttalink_upload_img_ack_pack(dst_addr, src_addr, msg,  count, ack, false);
}

/**
 * @brief Pack a upload_img_ack message, no crc
 * @param dst_addr 
 * @param src_addr
 * @param msg The TTAlink message to compress the data into
 *
 * @param count  .
 * @param ack  .
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t ttalink_upload_img_ack_pack_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t* msg,
                               uint32_t count, uint8_t ack)
{
    return _ttalink_upload_img_ack_pack(dst_addr, src_addr, msg,  count, ack, true);
}


static inline uint16_t _ttalink_upload_img_ack_pack_chan(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan,
                               ttalink_message_t* msg,
                                   uint32_t count,uint8_t ack, bool nocrc)
{
#if TTALINK_NEED_BYTE_SWAP || !TTALINK_ALIGNED_FIELDS
    char buf[TTALINK_MSG_ID_UPLOAD_IMG_ACK_LEN];
    _tta_put_uint32_t(buf, 0, count);
    _tta_put_uint8_t(buf, 4, ack);

        memcpy(_TTA_PAYLOAD_NON_CONST(msg), buf, TTALINK_MSG_ID_UPLOAD_IMG_ACK_LEN);
#else
    ttalink_upload_img_ack_t packet;
    packet.count = count;
    packet.ack = ack;

        memcpy(_TTA_PAYLOAD_NON_CONST(msg), &packet, TTALINK_MSG_ID_UPLOAD_IMG_ACK_LEN);
#endif

    msg->msgid = TTALINK_MSG_ID_UPLOAD_IMG_ACK;
    return ttalink_finalize_message_chan(msg, dst_addr, src_addr, chan, TTALINK_MSG_ID_UPLOAD_IMG_ACK_MIN_LEN, TTALINK_MSG_ID_UPLOAD_IMG_ACK_LEN, TTALINK_MSG_ID_UPLOAD_IMG_ACK_CRC, nocrc);
}

/**
 * @brief Pack a upload_img_ack message on a channel
 * @param dst_addr ID of this system
 * @param src_addr ID of this component (e.g. 200 for IMU)
 * @param chan The TTAlink channel this message will be sent over
 * @param msg The TTAlink message to compress the data into
 * @param count  .
 * @param ack  .
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t ttalink_upload_img_ack_pack_chan(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan,
                               ttalink_message_t* msg,
                                   uint32_t count,uint8_t ack)
{
    return _ttalink_upload_img_ack_pack_chan(dst_addr, src_addr, chan, msg,  count, ack, false);
}

/**
 * @brief Pack a upload_img_ack message on a channel, no crc
 * @param dst_addr ID of this system
 * @param src_addr ID of this component (e.g. 200 for IMU)
 * @param chan The TTAlink channel this message will be sent over
 * @param msg The TTAlink message to compress the data into
 * @param count  .
 * @param ack  .
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t ttalink_upload_img_ack_pack_chan_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan,
                               ttalink_message_t* msg,
                                   uint32_t count,uint8_t ack)
{
    return _ttalink_upload_img_ack_pack_chan(dst_addr, src_addr, chan, msg,  count, ack, true);
}


static inline uint16_t _ttalink_upload_img_ack_encode(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t* msg, const ttalink_upload_img_ack_t* upload_img_ack, bool nocrc)
{
    if(nocrc){
        return ttalink_upload_img_ack_pack_nocrc(dst_addr, src_addr, msg, upload_img_ack->count, upload_img_ack->ack);
    }else{
        return ttalink_upload_img_ack_pack(dst_addr, src_addr, msg, upload_img_ack->count, upload_img_ack->ack);
    }
    
}

/**
 * @brief Encode a upload_img_ack struct
 *
 * @param dst_addr ID of this system
 * @param src_addr ID of this component (e.g. 200 for IMU)
 * @param msg The TTAlink message to compress the data into
 * @param upload_img_ack C-struct to read the message contents from
 */
static inline uint16_t ttalink_upload_img_ack_encode(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t* msg, const ttalink_upload_img_ack_t* upload_img_ack)
{
    return _ttalink_upload_img_ack_encode(dst_addr, src_addr, msg, upload_img_ack, false);
}

/**
 * @brief Encode a upload_img_ack struct, no crc
 *
 * @param dst_addr ID of this system
 * @param src_addr ID of this component (e.g. 200 for IMU)
 * @param msg The TTAlink message to compress the data into
 * @param upload_img_ack C-struct to read the message contents from
 */
static inline uint16_t ttalink_upload_img_ack_encode_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t* msg, const ttalink_upload_img_ack_t* upload_img_ack)
{
    return _ttalink_upload_img_ack_encode(dst_addr, src_addr, msg, upload_img_ack, true);
}


static inline uint16_t _ttalink_upload_img_ack_encode_chan(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, ttalink_message_t* msg, const ttalink_upload_img_ack_t* upload_img_ack, bool nocrc)
{
    if(nocrc){
        return ttalink_upload_img_ack_pack_chan_nocrc(dst_addr, src_addr, chan, msg, upload_img_ack->count, upload_img_ack->ack);
    }else{
        return ttalink_upload_img_ack_pack_chan(dst_addr, src_addr, chan, msg, upload_img_ack->count, upload_img_ack->ack);
    }
}

/**
 * @brief Encode a upload_img_ack struct on a channel
 *
 * @param dst_addr ID of this system
 * @param src_addr ID of this component (e.g. 200 for IMU)
 * @param chan The TTAlink channel this message will be sent over
 * @param msg The TTAlink message to compress the data into
 * @param upload_img_ack C-struct to read the message contents from
 */
static inline uint16_t ttalink_upload_img_ack_encode_chan(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, ttalink_message_t* msg, const ttalink_upload_img_ack_t* upload_img_ack)
{
    return _ttalink_upload_img_ack_encode_chan(dst_addr, src_addr, chan, msg, upload_img_ack, false);
}

/**
 * @brief Encode a upload_img_ack struct on a channel, no crc
 *
 * @param dst_addr ID of this system
 * @param src_addr ID of this component (e.g. 200 for IMU)
 * @param chan The TTAlink channel this message will be sent over
 * @param msg The TTAlink message to compress the data into
 * @param upload_img_ack C-struct to read the message contents from
 */
static inline uint16_t ttalink_upload_img_ack_encode_chan_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, ttalink_message_t* msg, const ttalink_upload_img_ack_t* upload_img_ack)
{
    return _ttalink_upload_img_ack_encode_chan(dst_addr, src_addr, chan, msg, upload_img_ack, true);
}


#ifdef TTALINK_USE_CONVENIENCE_FUNCTIONS

static inline void _ttalink_upload_img_ack_send(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, uint32_t count, uint8_t ack, bool nocrc)
{
#if TTALINK_NEED_BYTE_SWAP || !TTALINK_ALIGNED_FIELDS
    char buf[TTALINK_MSG_ID_UPLOAD_IMG_ACK_LEN];
    _tta_put_uint32_t(buf, 0, count);
    _tta_put_uint8_t(buf, 4, ack);

    _tta_finalize_message_chan_send(dst_addr, src_addr, chan, TTALINK_MSG_ID_UPLOAD_IMG_ACK, buf, TTALINK_MSG_ID_UPLOAD_IMG_ACK_MIN_LEN, TTALINK_MSG_ID_UPLOAD_IMG_ACK_LEN, TTALINK_MSG_ID_UPLOAD_IMG_ACK_CRC, nocrc);
#else
    ttalink_upload_img_ack_t packet;
    packet.count = count;
    packet.ack = ack;

    _tta_finalize_message_chan_send(dst_addr, src_addr, chan, TTALINK_MSG_ID_UPLOAD_IMG_ACK, (const char *)&packet, TTALINK_MSG_ID_UPLOAD_IMG_ACK_MIN_LEN, TTALINK_MSG_ID_UPLOAD_IMG_ACK_LEN, TTALINK_MSG_ID_UPLOAD_IMG_ACK_CRC, nocrc);
#endif
}

/**
 * @brief Send a upload_img_ack message
 * @param chan TTAlink channel to send the message
 *
 * @param count  .
 * @param ack  .
 */
static inline void ttalink_upload_img_ack_send(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, uint32_t count, uint8_t ack)
{
    _ttalink_upload_img_ack_send(dst_addr, src_addr, chan, count, ack, false);
}

/**
 * @brief Send a upload_img_ack message, no crc
 * @param chan TTAlink channel to send the message
 *
 * @param count  .
 * @param ack  .
 */
static inline void ttalink_upload_img_ack_send_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, uint32_t count, uint8_t ack)
{
    _ttalink_upload_img_ack_send(dst_addr, src_addr, chan, count, ack, true);
}


static inline void _ttalink_upload_img_ack_send_struct(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, const ttalink_upload_img_ack_t* upload_img_ack, bool nocrc)
{
#if TTALINK_NEED_BYTE_SWAP || !TTALINK_ALIGNED_FIELDS
    if(nocrc){
        ttalink_upload_img_ack_send_nocrc(dst_addr, src_addr, chan, upload_img_ack->count, upload_img_ack->ack);
    }else{
        ttalink_upload_img_ack_send(dst_addr, src_addr, chan, upload_img_ack->count, upload_img_ack->ack);
    }
#else
    _tta_finalize_message_chan_send(dst_addr, src_addr, chan, TTALINK_MSG_ID_UPLOAD_IMG_ACK, (const char *)upload_img_ack, TTALINK_MSG_ID_UPLOAD_IMG_ACK_MIN_LEN, TTALINK_MSG_ID_UPLOAD_IMG_ACK_LEN, TTALINK_MSG_ID_UPLOAD_IMG_ACK_CRC, nocrc);
#endif
}

/**
 * @brief Send a upload_img_ack message
 * @param chan TTAlink channel to send the message
 * @param struct The TTAlink struct to serialize
 */
static inline void ttalink_upload_img_ack_send_struct(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, const ttalink_upload_img_ack_t* upload_img_ack)
{
    _ttalink_upload_img_ack_send_struct(dst_addr, src_addr, chan, upload_img_ack, false);
}

/**
 * @brief Send a upload_img_ack message, no crc
 * @param chan TTAlink channel to send the message
 * @param struct The TTAlink struct to serialize
 */
static inline void ttalink_upload_img_ack_send_struct_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, const ttalink_upload_img_ack_t* upload_img_ack)
{
    _ttalink_upload_img_ack_send_struct(dst_addr, src_addr, chan, upload_img_ack, true);
}

#if TTALINK_MSG_ID_UPLOAD_IMG_ACK_LEN <= TTALINK_MAX_PAYLOAD_LEN
static inline void _ttalink_upload_img_ack_send_buf(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t *msgbuf, ttalink_channel_t chan,  uint32_t count, uint8_t ack, bool nocrc)
{
#if TTALINK_NEED_BYTE_SWAP || !TTALINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _tta_put_uint32_t(buf, 0, count);
    _tta_put_uint8_t(buf, 4, ack);

    _tta_finalize_message_chan_send(dst_addr, src_addr, chan, TTALINK_MSG_ID_UPLOAD_IMG_ACK, buf, TTALINK_MSG_ID_UPLOAD_IMG_ACK_MIN_LEN, TTALINK_MSG_ID_UPLOAD_IMG_ACK_LEN, TTALINK_MSG_ID_UPLOAD_IMG_ACK_CRC, nocrc);
#else
    ttalink_upload_img_ack_t *packet = (ttalink_upload_img_ack_t *)msgbuf;
    packet->count = count;
    packet->ack = ack;

    _tta_finalize_message_chan_send(dst_addr, src_addr, chan, TTALINK_MSG_ID_UPLOAD_IMG_ACK, (const char *)packet, TTALINK_MSG_ID_UPLOAD_IMG_ACK_MIN_LEN, TTALINK_MSG_ID_UPLOAD_IMG_ACK_LEN, TTALINK_MSG_ID_UPLOAD_IMG_ACK_CRC, nocrc);
#endif
}

/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  ttalink_message_t which is the size of a full ttalink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void ttalink_upload_img_ack_send_buf(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t *msgbuf, ttalink_channel_t chan,  uint32_t count, uint8_t ack)
{
    _ttalink_upload_img_ack_send_buf(dst_addr, src_addr, msgbuf, chan, count, ack, false);
}

/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  ttalink_message_t which is the size of a full ttalink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage, no crc.
 */
static inline void ttalink_upload_img_ack_send_buf_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t *msgbuf, ttalink_channel_t chan,  uint32_t count, uint8_t ack)
{
    _ttalink_upload_img_ack_send_buf(dst_addr, src_addr, msgbuf, chan, count, ack, true);
}
#endif

#endif

// MESSAGE UPLOAD_IMG_ACK UNPACKING


/**
 * @brief Get field count from upload_img_ack message
 *
 * @return  .
 */
static inline uint32_t ttalink_upload_img_ack_get_count(const ttalink_message_t* msg)
{
    return _TTA_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field ack from upload_img_ack message
 *
 * @return  .
 */
static inline uint8_t ttalink_upload_img_ack_get_ack(const ttalink_message_t* msg)
{
    return _TTA_RETURN_uint8_t(msg,  4);
}

/**
 * @brief Decode a upload_img_ack message into a struct
 *
 * @param msg The message to decode
 * @param upload_img_ack C-struct to decode the message contents into
 */
static inline void ttalink_upload_img_ack_decode(const ttalink_message_t* msg, ttalink_upload_img_ack_t* upload_img_ack)
{
#if TTALINK_NEED_BYTE_SWAP || !TTALINK_ALIGNED_FIELDS
    upload_img_ack->count = ttalink_upload_img_ack_get_count(msg);
    upload_img_ack->ack = ttalink_upload_img_ack_get_ack(msg);
#else
        uint8_t len = msg->len < TTALINK_MSG_ID_UPLOAD_IMG_ACK_LEN? msg->len : TTALINK_MSG_ID_UPLOAD_IMG_ACK_LEN;
        memset(upload_img_ack, 0, TTALINK_MSG_ID_UPLOAD_IMG_ACK_LEN);
    memcpy(upload_img_ack, _TTA_PAYLOAD(msg), len);
#endif
}
