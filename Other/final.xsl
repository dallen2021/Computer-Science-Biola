<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:template match="/">
    <html>
      <head>
        <style>
          table {
            border: 1px solid gray;
          }
          th {
            background-color: gray;
            color: white;
          }
          td {
            border: 1px solid gray;
            padding: 5px;
          }
        </style>
      </head>
      <body>
        <table>
          <tr>
            <th>Name</th>
            <th>Chapters</th>
          </tr>
          <xsl:for-each select="Pentateuch_Books/Name">
            <tr>
              <td><xsl:value-of select="."/></td>
              <td><xsl:value-of select="Chapters"/></td>
            </tr>
          </xsl:for-each>
        </table>
      </body>
    </html>
  </xsl:template>
</xsl:stylesheet>