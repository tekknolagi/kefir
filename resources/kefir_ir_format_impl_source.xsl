<?xml version="1.0"?>
<xsl:stylesheet version="1.1"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:output method="text" encoding="utf-8" media-type="text/plain" />
    <xsl:variable name="lcletters">abcdefghijklmnopqrstuvwxyz</xsl:variable>
    <xsl:variable name="ucletters">ABCDEFGHIJKLMNOPQRSTUVWXYZ</xsl:variable>
	<xsl:template match="opcodes">
		<xsl:text>/*
    SPDX-License-Identifier: GPL-3.0

    Copyright (C) 2020-2021  Jevgenijs Protopopovs

    This file is part of Kefir project.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, version 3.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see &lt;http://www.gnu.org/licenses/&gt;.
*/

#include "kefir/ir/format_impl.h"
#include "kefir/core/util.h"
#include "kefir/core/error.h"

// Do not edit this file. It is autogenerated. Edit resources/opcodes.xml instead.
kefir_result_t kefir_ir_format_instr(struct kefir_json_output *json, const struct kefir_ir_module *module, const struct kefir_irinstr *instr) {
    REQUIRE(json != NULL, KEFIR_SET_ERROR(KEFIR_INTERNAL_ERROR, "Expected valid json output"));
    REQUIRE(module != NULL, KEFIR_SET_ERROR(KEFIR_INTERNAL_ERROR, "Expected valid IR module"));
    REQUIRE(instr != NULL, KEFIR_SET_ERROR(KEFIR_INTERNAL_ERROR, "Expected valid IR instruction"));
    switch (instr->opcode) {
</xsl:text>
		<xsl:for-each select="opcode">
			<xsl:text>        case KEFIR_IROPCODE_</xsl:text>
			<xsl:value-of select="translate(@id, $lcletters, $ucletters)" />
			<xsl:text>: return kefir_ir_format_instr_</xsl:text>
			<xsl:value-of select="@type" />
			<xsl:text>(json, module, instr);
</xsl:text>
		</xsl:for-each>
		<xsl:text>    }
    return KEFIR_SET_ERROR(KEFIR_INTERNAL_ERROR, "Unknown opcode");
}&#xa;</xsl:text>
	</xsl:template>

</xsl:stylesheet>