#include <QByteArray>

/* This method fixes the invalid JSON data which Juvenes API offers.
 * It's not pretty but has to be done.
 * Cleans dirty QByteArray so that it can be read to QJsonDocument.
 */
void cleanJSON(QByteArray &dirty) {
    // remove "}); from the end
   dirty.remove(dirty.length() - 4, 4);
   // remove ({"d":" from the beginning
   dirty.remove(0, 7);

   // Juvenes API is eh.. broken.
   // It's better you don't even try to think what
   // these lines of code do. Really, just go away.

   const char* remove = "\\\\\\\"";
   const char* replace = "";
   dirty.replace(remove, replace);

   remove = "\\\"";
   replace = "\"";
   dirty.replace(remove, replace);
}
