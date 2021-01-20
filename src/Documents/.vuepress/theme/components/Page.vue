<template>
  <main class="page">
    <slot name="top" />

    <Content class="theme-default-content" />
    <PageEdit />

    <PageNav v-bind="{ sidebarItems }" />

    <div class="page-footer">
      <ul class="inner">
        <li><a href="https://github.com/M2Team/NSudo/blob/master/License.md" target="_blank" rel="noopener noreferrer">MIT</a> Licensed &nbsp;</li>
        <li> Copyright&nbsp;&copy;&nbsp;2014&nbsp;<a href="https://m2team.github.io/" target="_blank" rel="noopener noreferrer">M2-Team</a></li>
      </ul>
    </div>

    <slot name="bottom" />
  </main>
</template>

<script>
import PageEdit from '@theme/components/PageEdit.vue'
import PageNav from '@theme/components/PageNav.vue'

export default {
  components: { PageEdit, PageNav },
  props: ['sidebarItems']
}
</script>

<style lang="stylus">
@require '../styles/wrapper.styl'

.page
  padding-bottom 2rem
  display block
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
      color $textColor
      font-size 12px

@media (max-width: $MQMobileNarrow)
  .page-footer
    .inner
      padding-left 0
      li
        display block
        line-height 1rem
</style>
