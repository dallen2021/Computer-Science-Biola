<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:template match = "food">
<html><head><title>Style sheet for test.xml</title></head>
<body><h2>Food Groups</h2>
<span style="font-family:Arial;font-size:12pt;color:red;"> Fruit: </span>
<xsl:value-of select = "fruit" /> <br />
<span style="font-family:Arial;font-size:12pt;color:green;"> Vegetable: </span>
<xsl:value-of select = "vegetable" /> <br />
<span style="font-family:Arial;font-size:12pt;color:brown;"> Grain: </span>
<xsl:value-of select = "grain" /> <br />
<span style="font-family:Arial;font-size:12pt;color:orange;"> Protein: </span>
<xsl:value-of select = "protein" /> <br />
</body></html>
</xsl:template></xsl:stylesheet>
