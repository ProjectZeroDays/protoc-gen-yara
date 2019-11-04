
/* Generated by the yara-pb compiler. DO NOT EDIT! */
#include <yara/mem.h>
#include <yara/modules.h>
#include "customer.pb-c.h"

#define MODULE_NAME pb_customer

static void* _pb_alloc(void *allocator_data, size_t size)
{
  return yr_malloc(size);
}

static void _pb_free(void *allocator_data, void *pointer)
{
  return yr_free(pointer);
}

begin_declarations;
  begin_struct("CreditCard");
    begin_struct("Status");
      declare_integer("VALID");
      declare_integer("CANCELLED");
    end_struct("Status");
  end_struct("CreditCard");
  declare_string("name");
  declare_integer("age");
  begin_struct_array("credit_cards");
    declare_string("number");
    begin_struct("expiration");
      declare_integer("year");
      declare_integer("month");
    end_struct("expiration");
    declare_integer("status");
  end_struct_array("credit_cards");
  declare_integer("premium");
end_declarations;

int module_initialize(
    YR_MODULE* module)
{
  return ERROR_SUCCESS;
}

int module_finalize(
    YR_MODULE* module)
{
  return ERROR_SUCCESS;
}

int module_unload(
    YR_OBJECT* module_object)
{
  return ERROR_SUCCESS;
}

int module_load(
    YR_SCAN_CONTEXT* context,
    YR_OBJECT* module_object,
    void* module_data,
    size_t module_data_size)
{
  ProtobufCAllocator allocator;

  allocator.alloc = _pb_alloc;
  allocator.free = _pb_free;

  Customer* pb = customer__unpack(&allocator, module_data_size, module_data);

  if (pb == NULL)
    return ERROR_INVALID_MODULE_DATA;

  set_integer(0, module_object, "CreditCard.Status.VALID");
  set_integer(1, module_object, "CreditCard.Status.CANCELLED");
  set_string(pb->name, module_object, "name");

  if (pb->has_age) {
    set_integer(pb->age, module_object, "age");
  }

  for (int i = 0; i < pb->n_credit_cards; i++) {

    if (pb->credit_cards[i] != NULL) {
      set_string(pb->credit_cards[i]->number, module_object, "credit_cards[%d].number", i);

      if (pb->credit_cards[i]->expiration != NULL) {

        if (pb->credit_cards[i]->expiration->has_year) {
          set_integer(pb->credit_cards[i]->expiration->year, module_object, "credit_cards[%d].expiration.year", i);
        }

        if (pb->credit_cards[i]->expiration->has_month) {
          set_integer(pb->credit_cards[i]->expiration->month, module_object, "credit_cards[%d].expiration.month", i);
        }
      }

      if (pb->credit_cards[i]->has_status) {
        set_integer(pb->credit_cards[i]->status, module_object, "credit_cards[%d].status", i);
      }
    }
  }

  if (pb->has_premium) {
    set_integer(pb->premium, module_object, "premium");
  }


  customer__free_unpacked(pb, &allocator);

  return ERROR_SUCCESS;
}
