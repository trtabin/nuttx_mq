#include <nuttx/config.h>
#include <mqueue.h>
#include <stdio.h>
#include "ble_display_link.h"

int display_task(int argc, char *argv[])
{
  mqd_t mq;
  struct ble_msg_s msg;
  ssize_t nbytes;

  mq = mq_open(MQ_NAME, O_RDONLY | O_CREAT, 0666, NULL);
  if (mq < 0)
    {
      perror("mq_open");
      return -1;
    }

  for (;;)
    {
      nbytes = mq_receive(mq, (char *)&msg, sizeof(msg), NULL);
      if (nbytes < 0)
        {
          perror("mq_receive");
          continue;
        }

      printf("Display received: %s\n", msg.text);
      /* TODO: update your actual display driver here */
    }

  mq_close(mq);
  return 0;
}
