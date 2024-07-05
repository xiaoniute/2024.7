#pragma once
// MESSAGE GENERAL_UPLOAD_IMG PACKING

#define TTALINK_MSG_ID_GENERAL_UPLOAD_IMG 4108

TTAPACKED(
typedef struct __ttalink_general_upload_img_t {
 int64_t sn; /*< 设备序列号.*/
 uint8_t device_type; /*< 设备类型.*/
 uint32_t count; /*<  .*/
 uint8_t size; /*<  .*/
 uint8_t data[250]; /*<  .*/
}) ttalink_general_upload_img_t;

#define TTALINK_MSG_ID_GENERAL_UPLOAD_IMG_LEN 264
#define TTALINK_MSG_ID_GENERAL_UPLOAD_IMG_MIN_LEN 264
#define TTALINK_MSG_ID_4108_LEN 264
#define TTALINK_MSG_ID_4108_MIN_LEN 264

#define TTALINK_MSG_ID_GENERAL_UPLOAD_IMG_CRC 196
#define TTALINK_MSG_ID_4108_CRC 196

#define TTALINK_MSG_GENERAL_UPLOAD_IMG_FIELD_DATA_LEN 250

#if TTALINK_COMMAND_24BIT
#define TTALINK_MESSAGE_INFO_GENERAL_UPLOAD_IMG { \
    4108, \
    "GENERAL_UPLOAD_IMG", \
    5, \
    {  { "sn", NULL, TTALINK_TYPE_INT64_T, 0, 0, offsetof(ttalink_general_upload_img_t, sn) }, \
         { "device_type", NULL, TTALINK_TYPE_UINT8_T, 0, 8, offsetof(ttalink_general_upload_img_t, device_type) }, \
         { "count", NULL, TTALINK_TYPE_UINT32_T, 0, 9, offsetof(ttalink_general_upload_img_t, count) }, \
         { "size", NULL, TTALINK_TYPE_UINT8_T, 0, 13, offsetof(ttalink_general_upload_img_t, size) }, \
         { "data", NULL, TTALINK_TYPE_UINT8_T, 250, 14, offsetof(ttalink_general_upload_img_t, data) }, \
         } \
}
#else
#define TTALINK_MESSAGE_INFO_GENERAL_UPLOAD_IMG { \
    "GENERAL_UPLOAD_IMG", \
    5, \
    {  { "sn", NULL, TTALINK_TYPE_INT64_T, 0, 0, offsetof(ttalink_general_upload_img_t, sn) }, \
         { "device_type", NULL, TTALINK_TYPE_UINT8_T, 0, 8, offsetof(ttalink_general_upload_img_t, device_type) }, \
         { "count", NULL, TTALINK_TYPE_UINT32_T, 0, 9, offsetof(ttalink_general_upload_img_t, count) }, \
         { "size", NULL, TTALINK_TYPE_UINT8_T, 0, 13, offsetof(ttalink_general_upload_img_t, size) }, \
         { "data", NULL, TTALINK_TYPE_UINT8_T, 250, 14, offsetof(ttalink_general_upload_img_t, data) }, \
         } \
}
#endif


static inline uint16_t _ttalink_general_upload_img_pack(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t* msg,
                               int64_t sn, uint8_t device_type, uint32_t count, uint8_t size, const uint8_t *data, bool nocrc)
{
#if TTALINK_NEED_BYTE_SWAP || !TTALINK_ALIGNED_FIELDS
    char buf[TTALINK_MSG_ID_GENERAL_UPLOAD_IMG_LEN];
    _tta_put_int64_t(buf, 0, sn);
    _tta_put_uint8_t(buf, 8, device_type);
    _tta_put_uint32_t(buf, 9, count);
    _tta_put_uint8_t(buf, 13, size);
    _tta_put_uint8_t_array(buf, 14, data, 250);
        memcpy(_TTA_PAYLOAD_NON_CONST(msg), buf, TTALINK_MSG_ID_GENERAL_UPLOAD_IMG_LEN);
#else
    ttalink_general_upload_img_t packet;
    packet.sn = sn;
    packet.device_type = device_type;
    packet.count = count;
    packet.size = size;
    tta_array_memcpy(packet.data, data, sizeof(uint8_t)*250);
        memcpy(_TTA_PAYLOAD_NON_CONST(msg), &packet, TTALINK_MSG_ID_GENERAL_UPLOAD_IMG_LEN);
#endif

    msg->msgid = TTALINK_MSG_ID_GENERAL_UPLOAD_IMG;
    return ttalink_finalize_message(msg, dst_addr, src_addr, TTALINK_MSG_ID_GENERAL_UPLOAD_IMG_MIN_LEN, TTALINK_MSG_ID_GENERAL_UPLOAD_IMG_LEN, TTALINK_MSG_ID_GENERAL_UPLOAD_IMG_CRC, nocrc);
}

/**
 * @brief Pack a general_upload_img message
 * @param dst_addr 
 * @param src_addr
 * @param msg The TTAlink message to compress the data into
 *
 * @param sn 设备序列号.
 * @param device_type 设备类型.
 * @param count  .
 * @param size  .
 * @param data  .
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t ttalink_general_upload_img_pack(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t* msg,
                               int64_t sn, uint8_t device_type, uint32_t count, uint8_t size, const uint8_t *data)
{
    return _ttalink_general_upload_img_pack(dst_addr, src_addr, msg,  sn, device_type, count, size, data, false);
}

/**
 * @brief Pack a general_upload_img message, no crc
 * @param dst_addr 
 * @param src_addr
 * @param msg The TTAlink message to compress the data into
 *
 * @param sn 设备序列号.
 * @param device_type 设备类型.
 * @param count  .
 * @param size  .
 * @param data  .
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t ttalink_general_upload_img_pack_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t* msg,
                               int64_t sn, uint8_t device_type, uint32_t count, uint8_t size, const uint8_t *data)
{
    return _ttalink_general_upload_img_pack(dst_addr, src_addr, msg,  sn, device_type, count, size, data, true);
}


static inline uint16_t _ttalink_general_upload_img_pack_chan(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan,
                               ttalink_message_t* msg,
                                   int64_t sn,uint8_t device_type,uint32_t count,uint8_t size,const uint8_t *data, bool nocrc)
{
#if TTALINK_NEED_BYTE_SWAP || !TTALINK_ALIGNED_FIELDS
    char buf[TTALINK_MSG_ID_GENERAL_UPLOAD_IMG_LEN];
    _tta_put_int64_t(buf, 0, sn);
    _tta_put_uint8_t(buf, 8, device_type);
    _tta_put_uint32_t(buf, 9, count);
    _tta_put_uint8_t(buf, 13, size);
    _tta_put_uint8_t_array(buf, 14, data, 250);
        memcpy(_TTA_PAYLOAD_NON_CONST(msg), buf, TTALINK_MSG_ID_GENERAL_UPLOAD_IMG_LEN);
#else
    ttalink_general_upload_img_t packet;
    packet.sn = sn;
    packet.device_type = device_type;
    packet.count = count;
    packet.size = size;
    tta_array_memcpy(packet.data, data, sizeof(uint8_t)*250);
        memcpy(_TTA_PAYLOAD_NON_CONST(msg), &packet, TTALINK_MSG_ID_GENERAL_UPLOAD_IMG_LEN);
#endif

    msg->msgid = TTALINK_MSG_ID_GENERAL_UPLOAD_IMG;
    return ttalink_finalize_message_chan(msg, dst_addr, src_addr, chan, TTALINK_MSG_ID_GENERAL_UPLOAD_IMG_MIN_LEN, TTALINK_MSG_ID_GENERAL_UPLOAD_IMG_LEN, TTALINK_MSG_ID_GENERAL_UPLOAD_IMG_CRC, nocrc);
}

/**
 * @brief Pack a general_upload_img message on a channel
 * @param dst_addr ID of this system
 * @param src_addr ID of this component (e.g. 200 for IMU)
 * @param chan The TTAlink channel this message will be sent over
 * @param msg The TTAlink message to compress the data into
 * @param sn 设备序列号.
 * @param device_type 设备类型.
 * @param count  .
 * @param size  .
 * @param data  .
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t ttalink_general_upload_img_pack_chan(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan,
                               ttalink_message_t* msg,
                                   int64_t sn,uint8_t device_type,uint32_t count,uint8_t size,const uint8_t *data)
{
    return _ttalink_general_upload_img_pack_chan(dst_addr, src_addr, chan, msg,  sn, device_type, count, size, data, false);
}

/**
 * @brief Pack a general_upload_img message on a channel, no crc
 * @param dst_addr ID of this system
 * @param src_addr ID of this component (e.g. 200 for IMU)
 * @param chan The TTAlink channel this message will be sent over
 * @param msg The TTAlink message to compress the data into
 * @param sn 设备序列号.
 * @param device_type 设备类型.
 * @param count  .
 * @param size  .
 * @param data  .
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t ttalink_general_upload_img_pack_chan_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan,
                               ttalink_message_t* msg,
                                   int64_t sn,uint8_t device_type,uint32_t count,uint8_t size,const uint8_t *data)
{
    return _ttalink_general_upload_img_pack_chan(dst_addr, src_addr, chan, msg,  sn, device_type, count, size, data, true);
}


static inline uint16_t _ttalink_general_upload_img_encode(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t* msg, const ttalink_general_upload_img_t* general_upload_img, bool nocrc)
{
    if(nocrc){
        return ttalink_general_upload_img_pack_nocrc(dst_addr, src_addr, msg, general_upload_img->sn, general_upload_img->device_type, general_upload_img->count, general_upload_img->size, general_upload_img->data);
    }else{
        return ttalink_general_upload_img_pack(dst_addr, src_addr, msg, general_upload_img->sn, general_upload_img->device_type, general_upload_img->count, general_upload_img->size, general_upload_img->data);
    }
    
}

/**
 * @brief Encode a general_upload_img struct
 *
 * @param dst_addr ID of this system
 * @param src_addr ID of this component (e.g. 200 for IMU)
 * @param msg The TTAlink message to compress the data into
 * @param general_upload_img C-struct to read the message contents from
 */
static inline uint16_t ttalink_general_upload_img_encode(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t* msg, const ttalink_general_upload_img_t* general_upload_img)
{
    return _ttalink_general_upload_img_encode(dst_addr, src_addr, msg, general_upload_img, false);
}

/**
 * @brief Encode a general_upload_img struct, no crc
 *
 * @param dst_addr ID of this system
 * @param src_addr ID of this component (e.g. 200 for IMU)
 * @param msg The TTAlink message to compress the data into
 * @param general_upload_img C-struct to read the message contents from
 */
static inline uint16_t ttalink_general_upload_img_encode_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t* msg, const ttalink_general_upload_img_t* general_upload_img)
{
    return _ttalink_general_upload_img_encode(dst_addr, src_addr, msg, general_upload_img, true);
}


static inline uint16_t _ttalink_general_upload_img_encode_chan(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, ttalink_message_t* msg, const ttalink_general_upload_img_t* general_upload_img, bool nocrc)
{
    if(nocrc){
        return ttalink_general_upload_img_pack_chan_nocrc(dst_addr, src_addr, chan, msg, general_upload_img->sn, general_upload_img->device_type, general_upload_img->count, general_upload_img->size, general_upload_img->data);
    }else{
        return ttalink_general_upload_img_pack_chan(dst_addr, src_addr, chan, msg, general_upload_img->sn, general_upload_img->device_type, general_upload_img->count, general_upload_img->size, general_upload_img->data);
    }
}

/**
 * @brief Encode a general_upload_img struct on a channel
 *
 * @param dst_addr ID of this system
 * @param src_addr ID of this component (e.g. 200 for IMU)
 * @param chan The TTAlink channel this message will be sent over
 * @param msg The TTAlink message to compress the data into
 * @param general_upload_img C-struct to read the message contents from
 */
static inline uint16_t ttalink_general_upload_img_encode_chan(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, ttalink_message_t* msg, const ttalink_general_upload_img_t* general_upload_img)
{
    return _ttalink_general_upload_img_encode_chan(dst_addr, src_addr, chan, msg, general_upload_img, false);
}

/**
 * @brief Encode a general_upload_img struct on a channel, no crc
 *
 * @param dst_addr ID of this system
 * @param src_addr ID of this component (e.g. 200 for IMU)
 * @param chan The TTAlink channel this message will be sent over
 * @param msg The TTAlink message to compress the data into
 * @param general_upload_img C-struct to read the message contents from
 */
static inline uint16_t ttalink_general_upload_img_encode_chan_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, ttalink_message_t* msg, const ttalink_general_upload_img_t* general_upload_img)
{
    return _ttalink_general_upload_img_encode_chan(dst_addr, src_addr, chan, msg, general_upload_img, true);
}


#ifdef TTALINK_USE_CONVENIENCE_FUNCTIONS

static inline void _ttalink_general_upload_img_send(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, int64_t sn, uint8_t device_type, uint32_t count, uint8_t size, const uint8_t *data, bool nocrc)
{
#if TTALINK_NEED_BYTE_SWAP || !TTALINK_ALIGNED_FIELDS
    char buf[TTALINK_MSG_ID_GENERAL_UPLOAD_IMG_LEN];
    _tta_put_int64_t(buf, 0, sn);
    _tta_put_uint8_t(buf, 8, device_type);
    _tta_put_uint32_t(buf, 9, count);
    _tta_put_uint8_t(buf, 13, size);
    _tta_put_uint8_t_array(buf, 14, data, 250);
    _tta_finalize_message_chan_send(dst_addr, src_addr, chan, TTALINK_MSG_ID_GENERAL_UPLOAD_IMG, buf, TTALINK_MSG_ID_GENERAL_UPLOAD_IMG_MIN_LEN, TTALINK_MSG_ID_GENERAL_UPLOAD_IMG_LEN, TTALINK_MSG_ID_GENERAL_UPLOAD_IMG_CRC, nocrc);
#else
    ttalink_general_upload_img_t packet;
    packet.sn = sn;
    packet.device_type = device_type;
    packet.count = count;
    packet.size = size;
    tta_array_memcpy(packet.data, data, sizeof(uint8_t)*250);
    _tta_finalize_message_chan_send(dst_addr, src_addr, chan, TTALINK_MSG_ID_GENERAL_UPLOAD_IMG, (const char *)&packet, TTALINK_MSG_ID_GENERAL_UPLOAD_IMG_MIN_LEN, TTALINK_MSG_ID_GENERAL_UPLOAD_IMG_LEN, TTALINK_MSG_ID_GENERAL_UPLOAD_IMG_CRC, nocrc);
#endif
}

/**
 * @brief Send a general_upload_img message
 * @param chan TTAlink channel to send the message
 *
 * @param sn 设备序列号.
 * @param device_type 设备类型.
 * @param count  .
 * @param size  .
 * @param data  .
 */
static inline void ttalink_general_upload_img_send(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, int64_t sn, uint8_t device_type, uint32_t count, uint8_t size, const uint8_t *data)
{
    _ttalink_general_upload_img_send(dst_addr, src_addr, chan, sn, device_type, count, size, data, false);
}

/**
 * @brief Send a general_upload_img message, no crc
 * @param chan TTAlink channel to send the message
 *
 * @param sn 设备序列号.
 * @param device_type 设备类型.
 * @param count  .
 * @param size  .
 * @param data  .
 */
static inline void ttalink_general_upload_img_send_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, int64_t sn, uint8_t device_type, uint32_t count, uint8_t size, const uint8_t *data)
{
    _ttalink_general_upload_img_send(dst_addr, src_addr, chan, sn, device_type, count, size, data, true);
}


static inline void _ttalink_general_upload_img_send_struct(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, const ttalink_general_upload_img_t* general_upload_img, bool nocrc)
{
#if TTALINK_NEED_BYTE_SWAP || !TTALINK_ALIGNED_FIELDS
    if(nocrc){
        ttalink_general_upload_img_send_nocrc(dst_addr, src_addr, chan, general_upload_img->sn, general_upload_img->device_type, general_upload_img->count, general_upload_img->size, general_upload_img->data);
    }else{
        ttalink_general_upload_img_send(dst_addr, src_addr, chan, general_upload_img->sn, general_upload_img->device_type, general_upload_img->count, general_upload_img->size, general_upload_img->data);
    }
#else
    _tta_finalize_message_chan_send(dst_addr, src_addr, chan, TTALINK_MSG_ID_GENERAL_UPLOAD_IMG, (const char *)general_upload_img, TTALINK_MSG_ID_GENERAL_UPLOAD_IMG_MIN_LEN, TTALINK_MSG_ID_GENERAL_UPLOAD_IMG_LEN, TTALINK_MSG_ID_GENERAL_UPLOAD_IMG_CRC, nocrc);
#endif
}

/**
 * @brief Send a general_upload_img message
 * @param chan TTAlink channel to send the message
 * @param struct The TTAlink struct to serialize
 */
static inline void ttalink_general_upload_img_send_struct(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, const ttalink_general_upload_img_t* general_upload_img)
{
    _ttalink_general_upload_img_send_struct(dst_addr, src_addr, chan, general_upload_img, false);
}

/**
 * @brief Send a general_upload_img message, no crc
 * @param chan TTAlink channel to send the message
 * @param struct The TTAlink struct to serialize
 */
static inline void ttalink_general_upload_img_send_struct_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, const ttalink_general_upload_img_t* general_upload_img)
{
    _ttalink_general_upload_img_send_struct(dst_addr, src_addr, chan, general_upload_img, true);
}

#if TTALINK_MSG_ID_GENERAL_UPLOAD_IMG_LEN <= TTALINK_MAX_PAYLOAD_LEN
static inline void _ttalink_general_upload_img_send_buf(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t *msgbuf, ttalink_channel_t chan,  int64_t sn, uint8_t device_type, uint32_t count, uint8_t size, const uint8_t *data, bool nocrc)
{
#if TTALINK_NEED_BYTE_SWAP || !TTALINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _tta_put_int64_t(buf, 0, sn);
    _tta_put_uint8_t(buf, 8, device_type);
    _tta_put_uint32_t(buf, 9, count);
    _tta_put_uint8_t(buf, 13, size);
    _tta_put_uint8_t_array(buf, 14, data, 250);
    _tta_finalize_message_chan_send(dst_addr, src_addr, chan, TTALINK_MSG_ID_GENERAL_UPLOAD_IMG, buf, TTALINK_MSG_ID_GENERAL_UPLOAD_IMG_MIN_LEN, TTALINK_MSG_ID_GENERAL_UPLOAD_IMG_LEN, TTALINK_MSG_ID_GENERAL_UPLOAD_IMG_CRC, nocrc);
#else
    ttalink_general_upload_img_t *packet = (ttalink_general_upload_img_t *)msgbuf;
    packet->sn = sn;
    packet->device_type = device_type;
    packet->count = count;
    packet->size = size;
    tta_array_memcpy(packet->data, data, sizeof(uint8_t)*250);
    _tta_finalize_message_chan_send(dst_addr, src_addr, chan, TTALINK_MSG_ID_GENERAL_UPLOAD_IMG, (const char *)packet, TTALINK_MSG_ID_GENERAL_UPLOAD_IMG_MIN_LEN, TTALINK_MSG_ID_GENERAL_UPLOAD_IMG_LEN, TTALINK_MSG_ID_GENERAL_UPLOAD_IMG_CRC, nocrc);
#endif
}

/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  ttalink_message_t which is the size of a full ttalink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void ttalink_general_upload_img_send_buf(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t *msgbuf, ttalink_channel_t chan,  int64_t sn, uint8_t device_type, uint32_t count, uint8_t size, const uint8_t *data)
{
    _ttalink_general_upload_img_send_buf(dst_addr, src_addr, msgbuf, chan, sn, device_type, count, size, data, false);
}

/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  ttalink_message_t which is the size of a full ttalink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage, no crc.
 */
static inline void ttalink_general_upload_img_send_buf_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t *msgbuf, ttalink_channel_t chan,  int64_t sn, uint8_t device_type, uint32_t count, uint8_t size, const uint8_t *data)
{
    _ttalink_general_upload_img_send_buf(dst_addr, src_addr, msgbuf, chan, sn, device_type, count, size, data, true);
}
#endif

#endif

// MESSAGE GENERAL_UPLOAD_IMG UNPACKING


/**
 * @brief Get field sn from general_upload_img message
 *
 * @return 设备序列号.
 */
static inline int64_t ttalink_general_upload_img_get_sn(const ttalink_message_t* msg)
{
    return _TTA_RETURN_int64_t(msg,  0);
}

/**
 * @brief Get field device_type from general_upload_img message
 *
 * @return 设备类型.
 */
static inline uint8_t ttalink_general_upload_img_get_device_type(const ttalink_message_t* msg)
{
    return _TTA_RETURN_uint8_t(msg,  8);
}

/**
 * @brief Get field count from general_upload_img message
 *
 * @return  .
 */
static inline uint32_t ttalink_general_upload_img_get_count(const ttalink_message_t* msg)
{
    return _TTA_RETURN_uint32_t(msg,  9);
}

/**
 * @brief Get field size from general_upload_img message
 *
 * @return  .
 */
static inline uint8_t ttalink_general_upload_img_get_size(const ttalink_message_t* msg)
{
    return _TTA_RETURN_uint8_t(msg,  13);
}

/**
 * @brief Get field data from general_upload_img message
 *
 * @return  .
 */
static inline uint16_t ttalink_general_upload_img_get_data(const ttalink_message_t* msg, uint8_t *data)
{
    return _TTA_RETURN_uint8_t_array(msg, data, 250,  14);
}

/**
 * @brief Decode a general_upload_img message into a struct
 *
 * @param msg The message to decode
 * @param general_upload_img C-struct to decode the message contents into
 */
static inline void ttalink_general_upload_img_decode(const ttalink_message_t* msg, ttalink_general_upload_img_t* general_upload_img)
{
#if TTALINK_NEED_BYTE_SWAP || !TTALINK_ALIGNED_FIELDS
    general_upload_img->sn = ttalink_general_upload_img_get_sn(msg);
    general_upload_img->device_type = ttalink_general_upload_img_get_device_type(msg);
    general_upload_img->count = ttalink_general_upload_img_get_count(msg);
    general_upload_img->size = ttalink_general_upload_img_get_size(msg);
    ttalink_general_upload_img_get_data(msg, general_upload_img->data);
#else
        uint8_t len = msg->len < TTALINK_MSG_ID_GENERAL_UPLOAD_IMG_LEN? msg->len : TTALINK_MSG_ID_GENERAL_UPLOAD_IMG_LEN;
        memset(general_upload_img, 0, TTALINK_MSG_ID_GENERAL_UPLOAD_IMG_LEN);
    memcpy(general_upload_img, _TTA_PAYLOAD(msg), len);
#endif
}
