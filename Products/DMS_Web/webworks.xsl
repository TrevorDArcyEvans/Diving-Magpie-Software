<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl">
<xsl:template match="/">
  <html>
  <body>
      <p><xsl:apply-templates select="MODEL/FILE_INFO"/></p>
      <p><xsl:apply-templates select="MODEL/MASS_PROPS"/></p>
  </body>
  </html>
</xsl:template>

<xsl:template match="FILE_INFO">
    <p>
    <b>File Info:</b>
    <p><img>
        <xsl:attribute name="src">
            <xsl:value-of select="BITMAP"/>
        </xsl:attribute>
    </img></p>

        <p>File name = <xsl:value-of select="NAME"/></p>
        <p>Size = <xsl:value-of select="SIZE"/> bytes</p>
        <p>File date = <xsl:value-of select="DATE"/></p>
    </p>
</xsl:template>

<xsl:template match="MASS_PROPS">
    <p>
    <b>Mass Properties:</b>
        <p>Length Units = <xsl:value-of select="LENGTH_UNITS"/></p>
        <p>Mass Units = <xsl:value-of select="MASS_UNITS"/></p>

        <p>Mass = <xsl:value-of select="MASS"/></p>
        <p>Area = <xsl:value-of select="AREA"/></p>
        <p>Volume = <xsl:value-of select="VOLUME"/></p>
        <p>Centre of mass = (
            <xsl:value-of select="CENTRE/X"/>,
            <xsl:value-of select="CENTRE/Y"/>,
            <xsl:value-of select="CENTRE/Z"/>)
        </p>

        <p><b>Moments of Inertia</b></p>
        <p>XX = <xsl:value-of select="MOMENT/XX"/></p>
        <p>YY = <xsl:value-of select="MOMENT/YY"/></p>
        <p>ZZ = <xsl:value-of select="MOMENT/ZZ"/></p>
        <p>XY = <xsl:value-of select="MOMENT/XY"/></p>
        <p>ZX = <xsl:value-of select="MOMENT/ZX"/></p>
        <p>YZ = <xsl:value-of select="MOMENT/YZ"/></p>

        <p><b>Box Dimensions</b></p>
        <p>X = <xsl:value-of select="BOX/X"/></p>
        <p>Y = <xsl:value-of select="BOX/Y"/></p>
        <p>Z = <xsl:value-of select="BOX/Z"/></p>
    </p>
</xsl:template>

</xsl:stylesheet>
