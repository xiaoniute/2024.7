#pragma once
// MESSAGE POD_1029_SET_PHOTO_MODE PACKING

#define TTALINK_MSG_ID_POD_1029_SET_PHOTO_MODE 11029

TTAPACKED(
typedef struct __ttalink_pod_1029_set_photo_mode_t {
 uint8_t type; /*<  Photo type
											1 :  Single engine;
											4 :  Continuous shooting mode;
											6 :  Interval shooting;*/
 uint8_t shooting_number; /*<  Number of consecutive shots (effective when the photo type is continuous).*/
 uint8_t timer_camera_number; /*<  number of photos taken regularly (effective when the type of photos taken is intermittent)
															0 :  reservation
															1-254 :  number of interval photos;
															255 :  keep shooting until the camera receives the stop interval shooting command.*/
 uint8_t photo_interval; /*<  Time interval between shots (effective when the type of shot is interval shot)
														0 :  reservation
														1-255 :  time interval between two shots (in seconds)*/
 uint8_t ack; /*<  */
}) ttalink_pod_1029_set_photo_mode_t;

#define TTALINK_MSG_ID_POD_1029_SET_PHOTO_MODE_LEN 5
#define TTALINK_MSG_ID_POD_1029_SET_PHOTO_MODE_MIN_LEN 5
#define TTALINK_MSG_ID_11029_LEN 5
#define TTALINK_MSG_ID_11029_MIN_LEN 5

#define TTALINK_MSG_ID_POD_1029_SET_PHOTO_MODE_CRC 185
#define TTALINK_MSG_ID_11029_CRC 185



#if TTALINK_COMMAND_24BIT
#define TTALINK_MESSAGE_INFO_POD_1029_SET_PHOTO_MODE { \
    11029, \
    "POD_1029_SET_PHOTO_MODE", \
    5, \
    {  { "type", NULL, TTALINK_TYPE_UINT8_T, 0, 0, offsetof(ttalink_pod_1029_set_photo_mode_t, type) }, \
         { "shooting_number", NULL, TTALINK_TYPE_UINT8_T, 0, 1, offsetof(ttalink_pod_1029_set_photo_mode_t, shooting_number) }, \
         { "timer_camera_number", NULL, TTALINK_TYPE_UINT8_T, 0, 2, offsetof(ttalink_pod_1029_set_photo_mode_t, timer_camera_number) }, \
         { "photo_interval", NULL, TTALINK_TYPE_UINT8_T, 0, 3, offsetof(ttalink_pod_1029_set_photo_mode_t, photo_interval) }, \
         { "ack", NULL, TTALINK_TYPE_UINT8_T, 0, 4, offsetof(ttalink_pod_1029_set_photo_mode_t, ack) }, \
         } \
}
#else
#define TTALINK_MESSAGE_INFO_POD_1029_SET_PHOTO_MODE { \
    "POD_1029_SET_PHOTO_MODE", \
    5, \
    {  { "type", NULL, TTALINK_TYPE_UINT8_T, 0, 0, offsetof(ttalink_pod_1029_set_photo_mode_t, type) }, \
         { "shooting_number", NULL, TTALINK_TYPE_UINT8_T, 0, 1, offsetof(ttalink_pod_1029_set_photo_mode_t, shooting_number) }, \
         { "timer_camera_number", NULL, TTALINK_TYPE_UINT8_T, 0, 2, offsetof(ttalink_pod_1029_set_photo_mode_t, timer_camera_number) }, \
         { "photo_interval", NULL, TTALINK_TYPE_UINT8_T, 0, 3, offsetof(ttalink_pod_1029_set_photo_mode_t, photo_interval) }, \
         { "ack", NULL, TTALINK_TYPE_UINT8_T, 0, 4, offsetof(ttalink_pod_1029_set_photo_mode_t, ack) }, \
         } \
}
#endif


static inline uint16_t _ttalink_pod_1029_set_photo_mode_pack(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t* msg,
                               uint8_t type, uint8_t shooting_number, uint8_t timer_camera_number, uint8_t photo_interval, uint8_t ack, bool nocrc)
{
#if TTALINK_NEED_BYTE_SWAP || !TTALINK_ALIGNED_FIELDS
    char buf[TTALINK_MSG_ID_POD_1029_SET_PHOTO_MODE_LEN];
    _tta_put_uint8_t(buf, 0, type);
    _tta_put_uint8_t(buf, 1, shooting_number);
    _tta_put_uint8_t(buf, 2, timer_camera_number);
    _tta_put_uint8_t(buf, 3, photo_interval);
    _tta_put_uint8_t(buf, 4, ack);

        memcpy(_TTA_PAYLOAD_NON_CONST(msg), buf, TTALINK_MSG_ID_POD_1029_SET_PHOTO_MODE_LEN);
#else
    ttalink_pod_1029_set_photo_mode_t packet;
    packet.type = type;
    packet.shooting_number = shooting_number;
    packet.timer_camera_number = timer_camera_number;
    packet.photo_interval = photo_interval;
    packet.ack = ack;

        memcpy(_TTA_PAYLOAD_NON_CONST(msg), &packet, TTALINK_MSG_ID_POD_1029_SET_PHOTO_MODE_LEN);
#endif

    msg->msgid = TTALINK_MSG_ID_POD_1029_SET_PHOTO_MODE;
    return ttalink_finalize_message(msg, dst_addr, src_addr, TTALINK_MSG_ID_POD_1029_SET_PHOTO_MODE_MIN_LEN, TTALINK_MSG_ID_POD_1029_SET_PHOTO_MODE_LEN, TTALINK_MSG_ID_POD_1029_SET_PHOTO_MODE_CRC, nocrc);
}

/**
 * @brief Pack a pod_1029_set_photo_mode message
 * @param dst_addr 
 * @param src_addr
 * @param msg The TTAlink message to compress the data into
 *
 * @param type  Photo type
											1 :  Single engine;
											4 :  Continuous shooting mode;
											6 :  Interval shooting;
 * @param shooting_number  Number of consecutive shots (effective when the photo type is continuous).
 * @param timer_camera_number  number of photos taken regularly (effective when the type of photos taken is intermittent)
															0 :  reservation
															1-254 :  number of interval photos;
															255 :  keep shooting until the camera receives the stop interval shooting command.
 * @param photo_interval  Time interval between shots (effective when the type of shot is interval shot)
														0 :  reservation
														1-255 :  time interval between two shots (in seconds)
 * @param ack  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t ttalink_pod_1029_set_photo_mode_pack(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t* msg,
                               uint8_t type, uint8_t shooting_number, uint8_t timer_camera_number, uint8_t photo_interval, uint8_t ack)
{
    return _ttalink_pod_1029_set_photo_mode_pack(dst_addr, src_addr, msg,  type, shooting_number, timer_camera_number, photo_interval, ack, false);
}

/**
 * @brief Pack a pod_1029_set_photo_mode message, no crc
 * @param dst_addr 
 * @param src_addr
 * @param msg The TTAlink message to compress the data into
 *
 * @param type  Photo type
											1 :  Single engine;
											4 :  Continuous shooting mode;
											6 :  Interval shooting;
 * @param shooting_number  Number of consecutive shots (effective when the photo type is continuous).
 * @param timer_camera_number  number of photos taken regularly (effective when the type of photos taken is intermittent)
															0 :  reservation
															1-254 :  number of interval photos;
															255 :  keep shooting until the camera receives the stop interval shooting command.
 * @param photo_interval  Time interval between shots (effective when the type of shot is interval shot)
														0 :  reservation
														1-255 :  time interval between two shots (in seconds)
 * @param ack  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t ttalink_pod_1029_set_photo_mode_pack_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t* msg,
                               uint8_t type, uint8_t shooting_number, uint8_t timer_camera_number, uint8_t photo_interval, uint8_t ack)
{
    return _ttalink_pod_1029_set_photo_mode_pack(dst_addr, src_addr, msg,  type, shooting_number, timer_camera_number, photo_interval, ack, true);
}


static inline uint16_t _ttalink_pod_1029_set_photo_mode_pack_chan(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan,
                               ttalink_message_t* msg,
                                   uint8_t type,uint8_t shooting_number,uint8_t timer_camera_number,uint8_t photo_interval,uint8_t ack, bool nocrc)
{
#if TTALINK_NEED_BYTE_SWAP || !TTALINK_ALIGNED_FIELDS
    char buf[TTALINK_MSG_ID_POD_1029_SET_PHOTO_MODE_LEN];
    _tta_put_uint8_t(buf, 0, type);
    _tta_put_uint8_t(buf, 1, shooting_number);
    _tta_put_uint8_t(buf, 2, timer_camera_number);
    _tta_put_uint8_t(buf, 3, photo_interval);
    _tta_put_uint8_t(buf, 4, ack);

        memcpy(_TTA_PAYLOAD_NON_CONST(msg), buf, TTALINK_MSG_ID_POD_1029_SET_PHOTO_MODE_LEN);
#else
    ttalink_pod_1029_set_photo_mode_t packet;
    packet.type = type;
    packet.shooting_number = shooting_number;
    packet.timer_camera_number = timer_camera_number;
    packet.photo_interval = photo_interval;
    packet.ack = ack;

        memcpy(_TTA_PAYLOAD_NON_CONST(msg), &packet, TTALINK_MSG_ID_POD_1029_SET_PHOTO_MODE_LEN);
#endif

    msg->msgid = TTALINK_MSG_ID_POD_1029_SET_PHOTO_MODE;
    return ttalink_finalize_message_chan(msg, dst_addr, src_addr, chan, TTALINK_MSG_ID_POD_1029_SET_PHOTO_MODE_MIN_LEN, TTALINK_MSG_ID_POD_1029_SET_PHOTO_MODE_LEN, TTALINK_MSG_ID_POD_1029_SET_PHOTO_MODE_CRC, nocrc);
}

/**
 * @brief Pack a pod_1029_set_photo_mode message on a channel
 * @param dst_addr ID of this system
 * @param src_addr ID of this component (e.g. 200 for IMU)
 * @param chan The TTAlink channel this message will be sent over
 * @param msg The TTAlink message to compress the data into
 * @param type  Photo type
											1 :  Single engine;
											4 :  Continuous shooting mode;
											6 :  Interval shooting;
 * @param shooting_number  Number of consecutive shots (effective when the photo type is continuous).
 * @param timer_camera_number  number of photos taken regularly (effective when the type of photos taken is intermittent)
															0 :  reservation
															1-254 :  number of interval photos;
															255 :  keep shooting until the camera receives the stop interval shooting command.
 * @param photo_interval  Time interval between shots (effective when the type of shot is interval shot)
														0 :  reservation
														1-255 :  time interval between two shots (in seconds)
 * @param ack  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t ttalink_pod_1029_set_photo_mode_pack_chan(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan,
                               ttalink_message_t* msg,
                                   uint8_t type,uint8_t shooting_number,uint8_t timer_camera_number,uint8_t photo_interval,uint8_t ack)
{
    return _ttalink_pod_1029_set_photo_mode_pack_chan(dst_addr, src_addr, chan, msg,  type, shooting_number, timer_camera_number, photo_interval, ack, false);
}

/**
 * @brief Pack a pod_1029_set_photo_mode message on a channel, no crc
 * @param dst_addr ID of this system
 * @param src_addr ID of this component (e.g. 200 for IMU)
 * @param chan The TTAlink channel this message will be sent over
 * @param msg The TTAlink message to compress the data into
 * @param type  Photo type
											1 :  Single engine;
											4 :  Continuous shooting mode;
											6 :  Interval shooting;
 * @param shooting_number  Number of consecutive shots (effective when the photo type is continuous).
 * @param timer_camera_number  number of photos taken regularly (effective when the type of photos taken is intermittent)
															0 :  reservation
															1-254 :  number of interval photos;
															255 :  keep shooting until the camera receives the stop interval shooting command.
 * @param photo_interval  Time interval between shots (effective when the type of shot is interval shot)
														0 :  reservation
														1-255 :  time interval between two shots (in seconds)
 * @param ack  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t ttalink_pod_1029_set_photo_mode_pack_chan_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan,
                               ttalink_message_t* msg,
                                   uint8_t type,uint8_t shooting_number,uint8_t timer_camera_number,uint8_t photo_interval,uint8_t ack)
{
    return _ttalink_pod_1029_set_photo_mode_pack_chan(dst_addr, src_addr, chan, msg,  type, shooting_number, timer_camera_number, photo_interval, ack, true);
}


static inline uint16_t _ttalink_pod_1029_set_photo_mode_encode(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t* msg, const ttalink_pod_1029_set_photo_mode_t* pod_1029_set_photo_mode, bool nocrc)
{
    if(nocrc){
        return ttalink_pod_1029_set_photo_mode_pack_nocrc(dst_addr, src_addr, msg, pod_1029_set_photo_mode->type, pod_1029_set_photo_mode->shooting_number, pod_1029_set_photo_mode->timer_camera_number, pod_1029_set_photo_mode->photo_interval, pod_1029_set_photo_mode->ack);
    }else{
        return ttalink_pod_1029_set_photo_mode_pack(dst_addr, src_addr, msg, pod_1029_set_photo_mode->type, pod_1029_set_photo_mode->shooting_number, pod_1029_set_photo_mode->timer_camera_number, pod_1029_set_photo_mode->photo_interval, pod_1029_set_photo_mode->ack);
    }
    
}

/**
 * @brief Encode a pod_1029_set_photo_mode struct
 *
 * @param dst_addr ID of this system
 * @param src_addr ID of this component (e.g. 200 for IMU)
 * @param msg The TTAlink message to compress the data into
 * @param pod_1029_set_photo_mode C-struct to read the message contents from
 */
static inline uint16_t ttalink_pod_1029_set_photo_mode_encode(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t* msg, const ttalink_pod_1029_set_photo_mode_t* pod_1029_set_photo_mode)
{
    return _ttalink_pod_1029_set_photo_mode_encode(dst_addr, src_addr, msg, pod_1029_set_photo_mode, false);
}

/**
 * @brief Encode a pod_1029_set_photo_mode struct, no crc
 *
 * @param dst_addr ID of this system
 * @param src_addr ID of this component (e.g. 200 for IMU)
 * @param msg The TTAlink message to compress the data into
 * @param pod_1029_set_photo_mode C-struct to read the message contents from
 */
static inline uint16_t ttalink_pod_1029_set_photo_mode_encode_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t* msg, const ttalink_pod_1029_set_photo_mode_t* pod_1029_set_photo_mode)
{
    return _ttalink_pod_1029_set_photo_mode_encode(dst_addr, src_addr, msg, pod_1029_set_photo_mode, true);
}


static inline uint16_t _ttalink_pod_1029_set_photo_mode_encode_chan(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, ttalink_message_t* msg, const ttalink_pod_1029_set_photo_mode_t* pod_1029_set_photo_mode, bool nocrc)
{
    if(nocrc){
        return ttalink_pod_1029_set_photo_mode_pack_chan_nocrc(dst_addr, src_addr, chan, msg, pod_1029_set_photo_mode->type, pod_1029_set_photo_mode->shooting_number, pod_1029_set_photo_mode->timer_camera_number, pod_1029_set_photo_mode->photo_interval, pod_1029_set_photo_mode->ack);
    }else{
        return ttalink_pod_1029_set_photo_mode_pack_chan(dst_addr, src_addr, chan, msg, pod_1029_set_photo_mode->type, pod_1029_set_photo_mode->shooting_number, pod_1029_set_photo_mode->timer_camera_number, pod_1029_set_photo_mode->photo_interval, pod_1029_set_photo_mode->ack);
    }
}

/**
 * @brief Encode a pod_1029_set_photo_mode struct on a channel
 *
 * @param dst_addr ID of this system
 * @param src_addr ID of this component (e.g. 200 for IMU)
 * @param chan The TTAlink channel this message will be sent over
 * @param msg The TTAlink message to compress the data into
 * @param pod_1029_set_photo_mode C-struct to read the message contents from
 */
static inline uint16_t ttalink_pod_1029_set_photo_mode_encode_chan(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, ttalink_message_t* msg, const ttalink_pod_1029_set_photo_mode_t* pod_1029_set_photo_mode)
{
    return _ttalink_pod_1029_set_photo_mode_encode_chan(dst_addr, src_addr, chan, msg, pod_1029_set_photo_mode, false);
}

/**
 * @brief Encode a pod_1029_set_photo_mode struct on a channel, no crc
 *
 * @param dst_addr ID of this system
 * @param src_addr ID of this component (e.g. 200 for IMU)
 * @param chan The TTAlink channel this message will be sent over
 * @param msg The TTAlink message to compress the data into
 * @param pod_1029_set_photo_mode C-struct to read the message contents from
 */
static inline uint16_t ttalink_pod_1029_set_photo_mode_encode_chan_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, ttalink_message_t* msg, const ttalink_pod_1029_set_photo_mode_t* pod_1029_set_photo_mode)
{
    return _ttalink_pod_1029_set_photo_mode_encode_chan(dst_addr, src_addr, chan, msg, pod_1029_set_photo_mode, true);
}


#ifdef TTALINK_USE_CONVENIENCE_FUNCTIONS

static inline void _ttalink_pod_1029_set_photo_mode_send(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, uint8_t type, uint8_t shooting_number, uint8_t timer_camera_number, uint8_t photo_interval, uint8_t ack, bool nocrc)
{
#if TTALINK_NEED_BYTE_SWAP || !TTALINK_ALIGNED_FIELDS
    char buf[TTALINK_MSG_ID_POD_1029_SET_PHOTO_MODE_LEN];
    _tta_put_uint8_t(buf, 0, type);
    _tta_put_uint8_t(buf, 1, shooting_number);
    _tta_put_uint8_t(buf, 2, timer_camera_number);
    _tta_put_uint8_t(buf, 3, photo_interval);
    _tta_put_uint8_t(buf, 4, ack);

    _tta_finalize_message_chan_send(dst_addr, src_addr, chan, TTALINK_MSG_ID_POD_1029_SET_PHOTO_MODE, buf, TTALINK_MSG_ID_POD_1029_SET_PHOTO_MODE_MIN_LEN, TTALINK_MSG_ID_POD_1029_SET_PHOTO_MODE_LEN, TTALINK_MSG_ID_POD_1029_SET_PHOTO_MODE_CRC, nocrc);
#else
    ttalink_pod_1029_set_photo_mode_t packet;
    packet.type = type;
    packet.shooting_number = shooting_number;
    packet.timer_camera_number = timer_camera_number;
    packet.photo_interval = photo_interval;
    packet.ack = ack;

    _tta_finalize_message_chan_send(dst_addr, src_addr, chan, TTALINK_MSG_ID_POD_1029_SET_PHOTO_MODE, (const char *)&packet, TTALINK_MSG_ID_POD_1029_SET_PHOTO_MODE_MIN_LEN, TTALINK_MSG_ID_POD_1029_SET_PHOTO_MODE_LEN, TTALINK_MSG_ID_POD_1029_SET_PHOTO_MODE_CRC, nocrc);
#endif
}

/**
 * @brief Send a pod_1029_set_photo_mode message
 * @param chan TTAlink channel to send the message
 *
 * @param type  Photo type
											1 :  Single engine;
											4 :  Continuous shooting mode;
											6 :  Interval shooting;
 * @param shooting_number  Number of consecutive shots (effective when the photo type is continuous).
 * @param timer_camera_number  number of photos taken regularly (effective when the type of photos taken is intermittent)
															0 :  reservation
															1-254 :  number of interval photos;
															255 :  keep shooting until the camera receives the stop interval shooting command.
 * @param photo_interval  Time interval between shots (effective when the type of shot is interval shot)
														0 :  reservation
														1-255 :  time interval between two shots (in seconds)
 * @param ack  
 */
static inline void ttalink_pod_1029_set_photo_mode_send(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, uint8_t type, uint8_t shooting_number, uint8_t timer_camera_number, uint8_t photo_interval, uint8_t ack)
{
    _ttalink_pod_1029_set_photo_mode_send(dst_addr, src_addr, chan, type, shooting_number, timer_camera_number, photo_interval, ack, false);
}

/**
 * @brief Send a pod_1029_set_photo_mode message, no crc
 * @param chan TTAlink channel to send the message
 *
 * @param type  Photo type
											1 :  Single engine;
											4 :  Continuous shooting mode;
											6 :  Interval shooting;
 * @param shooting_number  Number of consecutive shots (effective when the photo type is continuous).
 * @param timer_camera_number  number of photos taken regularly (effective when the type of photos taken is intermittent)
															0 :  reservation
															1-254 :  number of interval photos;
															255 :  keep shooting until the camera receives the stop interval shooting command.
 * @param photo_interval  Time interval between shots (effective when the type of shot is interval shot)
														0 :  reservation
														1-255 :  time interval between two shots (in seconds)
 * @param ack  
 */
static inline void ttalink_pod_1029_set_photo_mode_send_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, uint8_t type, uint8_t shooting_number, uint8_t timer_camera_number, uint8_t photo_interval, uint8_t ack)
{
    _ttalink_pod_1029_set_photo_mode_send(dst_addr, src_addr, chan, type, shooting_number, timer_camera_number, photo_interval, ack, true);
}


static inline void _ttalink_pod_1029_set_photo_mode_send_struct(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, const ttalink_pod_1029_set_photo_mode_t* pod_1029_set_photo_mode, bool nocrc)
{
#if TTALINK_NEED_BYTE_SWAP || !TTALINK_ALIGNED_FIELDS
    if(nocrc){
        ttalink_pod_1029_set_photo_mode_send_nocrc(dst_addr, src_addr, chan, pod_1029_set_photo_mode->type, pod_1029_set_photo_mode->shooting_number, pod_1029_set_photo_mode->timer_camera_number, pod_1029_set_photo_mode->photo_interval, pod_1029_set_photo_mode->ack);
    }else{
        ttalink_pod_1029_set_photo_mode_send(dst_addr, src_addr, chan, pod_1029_set_photo_mode->type, pod_1029_set_photo_mode->shooting_number, pod_1029_set_photo_mode->timer_camera_number, pod_1029_set_photo_mode->photo_interval, pod_1029_set_photo_mode->ack);
    }
#else
    _tta_finalize_message_chan_send(dst_addr, src_addr, chan, TTALINK_MSG_ID_POD_1029_SET_PHOTO_MODE, (const char *)pod_1029_set_photo_mode, TTALINK_MSG_ID_POD_1029_SET_PHOTO_MODE_MIN_LEN, TTALINK_MSG_ID_POD_1029_SET_PHOTO_MODE_LEN, TTALINK_MSG_ID_POD_1029_SET_PHOTO_MODE_CRC, nocrc);
#endif
}

/**
 * @brief Send a pod_1029_set_photo_mode message
 * @param chan TTAlink channel to send the message
 * @param struct The TTAlink struct to serialize
 */
static inline void ttalink_pod_1029_set_photo_mode_send_struct(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, const ttalink_pod_1029_set_photo_mode_t* pod_1029_set_photo_mode)
{
    _ttalink_pod_1029_set_photo_mode_send_struct(dst_addr, src_addr, chan, pod_1029_set_photo_mode, false);
}

/**
 * @brief Send a pod_1029_set_photo_mode message, no crc
 * @param chan TTAlink channel to send the message
 * @param struct The TTAlink struct to serialize
 */
static inline void ttalink_pod_1029_set_photo_mode_send_struct_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, const ttalink_pod_1029_set_photo_mode_t* pod_1029_set_photo_mode)
{
    _ttalink_pod_1029_set_photo_mode_send_struct(dst_addr, src_addr, chan, pod_1029_set_photo_mode, true);
}

#if TTALINK_MSG_ID_POD_1029_SET_PHOTO_MODE_LEN <= TTALINK_MAX_PAYLOAD_LEN
static inline void _ttalink_pod_1029_set_photo_mode_send_buf(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t *msgbuf, ttalink_channel_t chan,  uint8_t type, uint8_t shooting_number, uint8_t timer_camera_number, uint8_t photo_interval, uint8_t ack, bool nocrc)
{
#if TTALINK_NEED_BYTE_SWAP || !TTALINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _tta_put_uint8_t(buf, 0, type);
    _tta_put_uint8_t(buf, 1, shooting_number);
    _tta_put_uint8_t(buf, 2, timer_camera_number);
    _tta_put_uint8_t(buf, 3, photo_interval);
    _tta_put_uint8_t(buf, 4, ack);

    _tta_finalize_message_chan_send(dst_addr, src_addr, chan, TTALINK_MSG_ID_POD_1029_SET_PHOTO_MODE, buf, TTALINK_MSG_ID_POD_1029_SET_PHOTO_MODE_MIN_LEN, TTALINK_MSG_ID_POD_1029_SET_PHOTO_MODE_LEN, TTALINK_MSG_ID_POD_1029_SET_PHOTO_MODE_CRC, nocrc);
#else
    ttalink_pod_1029_set_photo_mode_t *packet = (ttalink_pod_1029_set_photo_mode_t *)msgbuf;
    packet->type = type;
    packet->shooting_number = shooting_number;
    packet->timer_camera_number = timer_camera_number;
    packet->photo_interval = photo_interval;
    packet->ack = ack;

    _tta_finalize_message_chan_send(dst_addr, src_addr, chan, TTALINK_MSG_ID_POD_1029_SET_PHOTO_MODE, (const char *)packet, TTALINK_MSG_ID_POD_1029_SET_PHOTO_MODE_MIN_LEN, TTALINK_MSG_ID_POD_1029_SET_PHOTO_MODE_LEN, TTALINK_MSG_ID_POD_1029_SET_PHOTO_MODE_CRC, nocrc);
#endif
}

/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  ttalink_message_t which is the size of a full ttalink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void ttalink_pod_1029_set_photo_mode_send_buf(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t *msgbuf, ttalink_channel_t chan,  uint8_t type, uint8_t shooting_number, uint8_t timer_camera_number, uint8_t photo_interval, uint8_t ack)
{
    _ttalink_pod_1029_set_photo_mode_send_buf(dst_addr, src_addr, msgbuf, chan, type, shooting_number, timer_camera_number, photo_interval, ack, false);
}

/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  ttalink_message_t which is the size of a full ttalink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage, no crc.
 */
static inline void ttalink_pod_1029_set_photo_mode_send_buf_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t *msgbuf, ttalink_channel_t chan,  uint8_t type, uint8_t shooting_number, uint8_t timer_camera_number, uint8_t photo_interval, uint8_t ack)
{
    _ttalink_pod_1029_set_photo_mode_send_buf(dst_addr, src_addr, msgbuf, chan, type, shooting_number, timer_camera_number, photo_interval, ack, true);
}
#endif

#endif

// MESSAGE POD_1029_SET_PHOTO_MODE UNPACKING


/**
 * @brief Get field type from pod_1029_set_photo_mode message
 *
 * @return  Photo type
											1 :  Single engine;
											4 :  Continuous shooting mode;
											6 :  Interval shooting;
 */
static inline uint8_t ttalink_pod_1029_set_photo_mode_get_type(const ttalink_message_t* msg)
{
    return _TTA_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field shooting_number from pod_1029_set_photo_mode message
 *
 * @return  Number of consecutive shots (effective when the photo type is continuous).
 */
static inline uint8_t ttalink_pod_1029_set_photo_mode_get_shooting_number(const ttalink_message_t* msg)
{
    return _TTA_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Get field timer_camera_number from pod_1029_set_photo_mode message
 *
 * @return  number of photos taken regularly (effective when the type of photos taken is intermittent)
															0 :  reservation
															1-254 :  number of interval photos;
															255 :  keep shooting until the camera receives the stop interval shooting command.
 */
static inline uint8_t ttalink_pod_1029_set_photo_mode_get_timer_camera_number(const ttalink_message_t* msg)
{
    return _TTA_RETURN_uint8_t(msg,  2);
}

/**
 * @brief Get field photo_interval from pod_1029_set_photo_mode message
 *
 * @return  Time interval between shots (effective when the type of shot is interval shot)
														0 :  reservation
														1-255 :  time interval between two shots (in seconds)
 */
static inline uint8_t ttalink_pod_1029_set_photo_mode_get_photo_interval(const ttalink_message_t* msg)
{
    return _TTA_RETURN_uint8_t(msg,  3);
}

/**
 * @brief Get field ack from pod_1029_set_photo_mode message
 *
 * @return  
 */
static inline uint8_t ttalink_pod_1029_set_photo_mode_get_ack(const ttalink_message_t* msg)
{
    return _TTA_RETURN_uint8_t(msg,  4);
}

/**
 * @brief Decode a pod_1029_set_photo_mode message into a struct
 *
 * @param msg The message to decode
 * @param pod_1029_set_photo_mode C-struct to decode the message contents into
 */
static inline void ttalink_pod_1029_set_photo_mode_decode(const ttalink_message_t* msg, ttalink_pod_1029_set_photo_mode_t* pod_1029_set_photo_mode)
{
#if TTALINK_NEED_BYTE_SWAP || !TTALINK_ALIGNED_FIELDS
    pod_1029_set_photo_mode->type = ttalink_pod_1029_set_photo_mode_get_type(msg);
    pod_1029_set_photo_mode->shooting_number = ttalink_pod_1029_set_photo_mode_get_shooting_number(msg);
    pod_1029_set_photo_mode->timer_camera_number = ttalink_pod_1029_set_photo_mode_get_timer_camera_number(msg);
    pod_1029_set_photo_mode->photo_interval = ttalink_pod_1029_set_photo_mode_get_photo_interval(msg);
    pod_1029_set_photo_mode->ack = ttalink_pod_1029_set_photo_mode_get_ack(msg);
#else
        uint8_t len = msg->len < TTALINK_MSG_ID_POD_1029_SET_PHOTO_MODE_LEN? msg->len : TTALINK_MSG_ID_POD_1029_SET_PHOTO_MODE_LEN;
        memset(pod_1029_set_photo_mode, 0, TTALINK_MSG_ID_POD_1029_SET_PHOTO_MODE_LEN);
    memcpy(pod_1029_set_photo_mode, _TTA_PAYLOAD(msg), len);
#endif
}
