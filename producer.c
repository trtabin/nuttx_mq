#include <nuttx/config.h>
#include <mqueue.h>
#include <stdio.h>
#include <string.h>
#include "ble_display_link.h"

int ble_task(int argc, char *argv[])
{
  mqd_t mq;
  struct mq_attr attr;
  struct ble_msg_s msg;
  int ret;

  attr.mq_maxmsg = MAX_MSG_COUNT;
  attr.mq_msgsize = sizeof(struct ble_msg_s);
  attr.mq_flags = 0;

  /* Open or create the queue */
  mq = mq_open(MQ_NAME, O_WRONLY | O_CREAT, 0666, &attr);
  if (mq < 0)
    {
      perror("mq_open");
      return -1;
    }

  for (;;)
    {
      /* Simulate BLE data reception */
      snprintf(msg.text, sizeof(msg.text), "BLE Data: %d", up_rtc_time());

      /* Send to display task */
      ret = mq_send(mq, (char *)&msg, sizeof(msg), 0);
      if (ret < 0)
        {
          perror("mq_send");
        }

      sleep(1);  // simulate periodic BLE packets
    }

  mq_close(mq);
  return 0;
}
