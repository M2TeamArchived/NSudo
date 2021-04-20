<template>
  <div class="page-footer">
    <ul class="inner">    
      <li v-for="item in footer" :key="item.link">
        <a v-if="item.link" :href="item.link" target="_blank" rel="noopener noreferrer">{{ item.text }}</a>
        <template v-else><span v-html="item.text">{{ item.text }}</span></template>
      </li>
    </ul>
  </div>
</template>
<script>
export default {
  computed: {
    footer () {
      return this.$themeLocaleConfig.footer || this.$site.themeConfig.footer || []
    }
  }
};
</script>
<style lang="stylus">
@require '../styles/wrapper.styl'
.page-footer
  @extend $wrapper
  padding 0 2.5rem
  .inner
    border-top 1px solid $borderColor
    padding-top 2rem
    text-align center
    margin 0
    li
      display inline-block
      padding 0 10px
      border-right 1px solid #ccc
      color $textColor
      font-size 12px
      &:first-child
        padding-left 0
      &:last-child
        border-right none
        padding-right 0
      img 
        vertical-align middle
        margin-right 8px
@media (max-width: $MQMobileNarrow)
  .page-footer
    padding 0 1.5rem
    .inner
      li
        display block
        border none
        padding 0
        line-height 1rem
</style>
