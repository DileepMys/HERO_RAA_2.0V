#ifndef CAN_STACK_COMMON_TYPES_H
#define CAN_STACK_COMMON_TYPES_H


/**
 * @brief Represents the hardware object handles of a CAN hardware unit.
*/
typedef uint8_t Can_HwHandleType;

/** \brief typedef  Can_IdType
 *
 *  Represents the identifier of an L-PDU. For extended IDs the most significant
 ** bit is set.
 */
typedef uint32_t Can_IdType;

typedef uint16_t PduIdType;

typedef struct can_pdutype_struct
{
  /** ID of the CAN message */
  Can_IdType id;
  /** Length of the message in bytes */
  uint8_t length;
  /** Pointer to the message buffer in RAM */
  const uint8_t* sdu;
  /** Pdu Handle */
  PduIdType swPduHandle;

} Can_PduType;

#endif
