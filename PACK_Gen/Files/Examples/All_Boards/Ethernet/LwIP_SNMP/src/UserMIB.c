#include "UserMIB.h"
#include <MDRB_LEDs.h>
#include <MDRB_Buttons.h>

static s16_t get_switches_value(struct snmp_node_instance* instance, void* value);
static s16_t get_leds_value(struct snmp_node_instance* instance, void* value);
static snmp_err_t set_leds_value(struct snmp_node_instance* instance, u16_t len, void *value);


static const struct snmp_scalar_node leds_node = SNMP_SCALAR_CREATE_NODE(
		1, SNMP_NODE_INSTANCE_READ_WRITE, SNMP_ASN1_TYPE_INTEGER, get_leds_value, NULL, set_leds_value);


/* led .1.3.6.1.4.1.26381.1.2 */
static const struct snmp_scalar_node switches_node = SNMP_SCALAR_CREATE_NODE_READONLY( 2, SNMP_ASN1_TYPE_INTEGER, get_switches_value);

/* led nodes  .1.3.6.1.4.1.26381.1 */
static const struct snmp_node* const gpio_nodes[] = { &switches_node.node.node, &leds_node.node.node };
static const struct snmp_tree_node   gpio_tree_node = SNMP_CREATE_TREE_NODE(1, gpio_nodes);

static const u32_t my_base_oid[] = { 1, 3, 6, 1, 4, 1, 26381, 1 };

const struct snmp_mib user_MIB = SNMP_MIB_CREATE(my_base_oid, &gpio_tree_node.node);

static uint32_t ledState = 0;

void MIB_HandlersInit(void)
{
  MDRB_Buttons_InitTick(0);
  MDRB_LED_Init(MDRB_LED_1);
  ledState = 0;
}


static s16_t get_switches_value(struct snmp_node_instance* instance, void* value)
{
  *((uint32_t*) value) = MDRB_BntPushed_Up(false);
  return sizeof(uint32_t);  
}

static s16_t get_leds_value(struct snmp_node_instance* instance, void* value)
{
  *((uint32_t*) value) = ledState;  
  return sizeof(ledState);
}

static snmp_err_t set_leds_value(struct snmp_node_instance* instance, u16_t len, void *value)
{
  ledState = *(uint32_t *)value & 0x1UL;  
  MDRB_LED_Set(MDRB_LED_1, ledState);
  
  return SNMP_ERR_NOERROR;
}

